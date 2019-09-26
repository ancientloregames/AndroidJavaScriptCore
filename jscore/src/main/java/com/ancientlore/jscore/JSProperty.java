package com.ancientlore.jscore;

import androidx.annotation.Nullable;

import org.jetbrains.annotations.NotNull;


public final class JSProperty<T>
{
    private final JSObject parent;

    private final Class type;

    private final String name;

    public JSProperty(@NotNull JSObject parent, @NotNull String name, @NotNull Class type)
    {
        this.parent = parent;
        this.name = name;
        this.type = type;
        parent.property(name, new JSValue(parent.context));
    }

    public void set(T value)
    {
        parent.property(name, JSUtils.toJSValue(parent.context, value));
    }

    /**
     * @return the current property value. Or null, if:
     * 1. the generic type is incompatible with the type of this property in JS
     * 2. property in JS is either null, or undefined
     */
    @Nullable
    public T get()
    {
        JSValue jsValue = parent.property(name);

        if (JSUtils.isConvertable(jsValue)) {
            Object value = null;
            if (jsValue.isNumber()) {
                if (type == Integer.class)
                    value = jsValue.toNumber().intValue();
                else if (type == Float.class)
                    value = jsValue.toNumber().floatValue();
                else if (type == Double.class)
                    value = jsValue.toNumber();
                else if (type == Long.class)
                    value = jsValue.toNumber().longValue();
                else if (type == Short.class)
                    value = jsValue.toNumber().shortValue();
            }
            else if (type == Boolean.class && jsValue.isBoolean())
                value = jsValue.toBoolean();
            else if (type == String.class && jsValue.isString())
                value = toString();
            else if (type == JSObject.class && jsValue.isObject())
                value = jsValue.toObject();
            else if (type == JSFunction.class && jsValue.isFunction())
                value = jsValue.toFunction();
            else if (type == JSArray.class && jsValue.isArray())
                value = jsValue.toJSArray();

            return (T) value;
        }
        return null;
    }
}
