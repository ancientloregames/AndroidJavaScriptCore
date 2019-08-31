package com.ancientlore.jscore;

import android.util.Log;

import androidx.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.ParameterizedType;

public class JSProxy extends JSObject {
    private static final String TAG = JSObject.class.getSimpleName();

    public static final int TARGET_CONTEXT = 0;
    public static final int TARGET_THIS = 1;

    @IntDef({TARGET_CONTEXT, TARGET_THIS})
    @Retention(RetentionPolicy.SOURCE)
    public @interface ExportTarget {
    }

    @ExportTarget
    private final int exportTarget;

    public JSProxy(JSContext context) {
        this(context, TARGET_THIS);
    }

    public JSProxy(final JSContext context, @ExportTarget int exportTarget) {
        this.context = context;
        this.exportTarget = exportTarget;
        context.sync(new Runnable() {
            @Override
            public void run() {
                valueRef = make(context.ctxRef(), 0L);
                registerFields();
                registerMethods();
            }
        });
        context.persistObject(this);
    }

    /**
     * Java fields export to JS:
     * 	1. JSProperty are exporting automatically
     * 	2. Others - if the @jsexport annotation presents
     */
    private void registerFields()
    {
        Field[] fields = getClass().getFields();
        for (Field field : fields)
        {
            Class type = field.getType();
            if (type == JSProperty.class) {
                try {
                    Constructor<JSProperty> cons = type.getDeclaredConstructor(JSContext.class, Class.class);
                    field.setAccessible(true);
                    Class genericClass = (Class) ((ParameterizedType) field.getGenericType()).getActualTypeArguments()[0];
                    JSProperty prop = cons.newInstance(context, genericClass);
                    field.set(this, prop);
                    property(field.getName(), prop);
                } catch (InstantiationException e) { e.printStackTrace();
                } catch (InvocationTargetException e) { e.printStackTrace();
                } catch (NoSuchMethodException e) { e.printStackTrace();
                } catch (IllegalAccessException e) { e.printStackTrace(); }
            }
            else if (field.isAnnotationPresent(jsexport.class)) {
                try {
                    field.setAccessible(true);
                    if (exportTarget == TARGET_THIS)
                        property(field.getName(), field.get(this));
                    else context.property(field.getName(), field.get(this));
                } catch (IllegalAccessException e) {
                    Log.e(TAG, "The field " + field.getName() + " is signed " +
                            "for export to js, has a private access modificator");
                }
            }
        }
    }

    private void registerMethods() {
        Method[] methods = getClass().getMethods();
        for (Method method : methods) {
            if (!method.isBridge() && method.isAnnotationPresent(jsexport.class)) {
                JSFunction f = new JSFunction(context, method, JSObject.class, this);
                if (exportTarget == TARGET_THIS)
                    property(method.getName(), f);
                else context.property(method.getName(), f);
            }
        }
    }
}
