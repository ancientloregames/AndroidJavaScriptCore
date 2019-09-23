package com.ancientlore.jscore;

import androidx.annotation.Nullable;

import org.jetbrains.annotations.Contract;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class JSUtils {

    private JSUtils() { }

    @Nullable
    @Contract("null, _ -> null")
    public static Object toJavaObject(JSValue jsValue)
    {
        if (isNotConvertable(jsValue))
            return null;
        else if (jsValue.isBoolean())
            return jsValue.toBoolean();
        else if (jsValue.isNumber())
            return jsValue.toNumber();
        else if (jsValue.isString())
            return jsValue.toString();
        else if (jsValue.isArray())
            return toList(jsValue.toJSArray());
        else if (jsValue.isFunction())
            return jsValue.toFunction();
        else if (jsValue.isObject())
            return toMap(jsValue.toObject());
        else
            return null;
    }

    @Nullable
    public static List<Object> toList(JSBaseArray<JSValue> jsArray) {

        if (isConvertable(jsArray)) {

            List<Object> result = new ArrayList<>();

            for (JSValue jsValue : jsArray) {

                Object object = toJavaObject(jsValue);
                if (object != null)
                    result.add(object);
            }
            return result;
        }
        return null;
    }

    @Nullable
    public static <T> List<T> toList(JSBaseArray<JSValue> jsArray, Class<T> clazz)
    {
        if (isConvertable(jsArray)) {

            List<T> result = new ArrayList<>();

            for (JSValue jsValue : jsArray) {

                Object object = toJavaObject(jsValue);
                if (object != null && object.getClass().isAssignableFrom(clazz))
                    result.add((T) object);
            }
            return result;
        }
        return null;
    }

    @Nullable
    public static Map<String, Object> toMap(JSObject jsObject) {

        if (isConvertable(jsObject)) {

            Map<String, Object> result = new HashMap<>();

            for (String key : jsObject.propertyNames()) {

                Object object = toJavaObject(jsObject.property(key));
                if (object != null)
                    result.put(key, object);
            }
            return result;
        }
        return null;
    }

    @Nullable
    public static <T> Map<String, T> toMap(JSObject jsObject, Class<T> clazz) {

        if (isConvertable(jsObject)) {

            Map<String, T> result = new HashMap<>();

            for (String key : jsObject.propertyNames()) {

                Object object = toJavaObject(jsObject.property(key));
                if (object != null && object.getClass().isAssignableFrom(clazz))
                    result.put(key, (T) object);
            }
            return result;
        }
        return null;
    }

    @Contract("null -> false")
    public static boolean isConvertable(JSValue jsValue)
    {
        return jsValue != null && jsValue.isDefined() && jsValue.isNotNull();
    }

    @Contract("null -> true")
    public static boolean isNotConvertable(JSValue jsValue)
    {
        return !isConvertable(jsValue);
    }
}
