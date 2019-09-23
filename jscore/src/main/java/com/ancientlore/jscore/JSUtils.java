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
    public static List<Object> toList(JSBaseArray<JSValue> jsArray) {

        if (isConvertable(jsArray)) {

            List<Object> result = new ArrayList<>();

            for (JSValue jsValue : jsArray) {

                if (isNotConvertable(jsValue))
                    continue;
                else if (jsValue.isBoolean())
                    result.add(jsValue.toBoolean());
                else if (jsValue.isNumber())
                    result.add(jsValue.toNumber());
                else if (jsValue.isString())
                    result.add(jsValue.toString());
                else if (jsValue.isArray())
                    result.add(toList(jsValue.toJSArray()));
                else if (jsValue.isFunction())
                    result.add(jsValue.toFunction());
                else if (jsValue.isObject())
                    result.add(toMap(jsValue.toObject()));
            }
            return result;
        }
        return null;
    }

    @Nullable
    public static Map toMap(JSObject jsObject) {

        if (isConvertable(jsObject)) {

            Map<String, Object> result = new HashMap<>();

            for (String key : jsObject.propertyNames()) {

                JSValue jsValue = jsObject.property(key);

                if (isNotConvertable(jsValue))
                    continue;
                if (jsValue.isBoolean())
                    result.put(key, jsValue.toBoolean());
                else if (jsValue.isNumber())
                    result.put(key, jsValue.toNumber());
                else if (jsValue.isString())
                    result.put(key, jsValue.toString());
                else if (jsValue.isArray())
                    result.put(key, toList(jsValue.toJSArray()));
                else if (jsValue.isFunction())
                    result.put(key, jsValue.toFunction());
                else if (jsValue.isObject())
                    result.put(key, toMap(jsValue.toObject()));
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
