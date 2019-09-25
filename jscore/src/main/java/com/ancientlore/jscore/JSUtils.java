package com.ancientlore.jscore;

import androidx.annotation.Nullable;

import org.jetbrains.annotations.Contract;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public final class JSUtils {

    private JSUtils() { }

    @Nullable
    @Contract("null -> null")
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

    @Nullable
    @Contract("null -> null")
    public static Object toJavaObjectJson(JSValue jsValue)
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
            return toJsonArray(jsValue.toJSArray());
        else if (jsValue.isFunction())
            return jsValue.toFunction();
        else if (jsValue.isObject())
            return toJsonObject(jsValue.toObject());
        else
            return null;
    }

    @Nullable
    @Contract("null -> null")
    public static JSONObject toJsonObject(JSObject jsObject)
    {
        if (isConvertable(jsObject)) {

            JSONObject result = new JSONObject();

            for (String key : jsObject.propertyNames()) {

                Object object = toJavaObjectJson(jsObject.property(key));

                if (object != null)
                {
                    try {
                        result.put(key, object);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
            return result;
        }
        return null;
    }

    @Nullable
    @Contract("null -> null")
    public static JSONArray toJsonArray(JSBaseArray<JSValue> jsArray)
    {
        if (isConvertable(jsArray)) {

            JSONArray result = new JSONArray();

            for (JSValue jsValue : jsArray) {

                Object object = toJavaObjectJson(jsValue);
                if (object != null)
                    result.put(object);
            }
            return result;
        }
        return null;
    }

    @Nullable
    @Contract("null, _ -> null")
    public static JSValue toJSValue(JSContext context, Object object)
    {
        JSValue result;

        if (object instanceof JSValue)
            result = (JSValue) object;
        else if (object instanceof String
                || object instanceof Boolean
                || object instanceof Number)
            result = new JSValue(context, object);
        else if (object instanceof Map)
            result = toJSObject(context, (Map) object);
        else if (object instanceof Collection)
            result = toJSArray(context, (Collection) object);
        else if (object instanceof JSONObject)
            result = toJSObject(context, (JSONObject) object);
        else if (object instanceof JSONArray)
            result = toJSArray(context, (JSONArray) object);
        else if (object != null && object.getClass().isArray())
            result = toJSArray(context, (Object[]) object);
        else if (context != null) {
            if (object == null)
                result = new JSValue(context, null);
            else result = new JSValue(context);
        }
        else result = null;

        return result;
    }

    @Nullable
    @Contract("null, _ -> null; !null, null -> null")
    public static JSArray<JSValue> toJSArray(JSContext context, Collection collection)
    {
        if (context != null && collection != null) {
            JSArray<JSValue> result = new JSArray(context, JSValue.class);

            Iterator iter = collection.iterator();
            while (iter.hasNext()) {
                result.add(toJSValue(context, iter.next()));
            }

            return result;
        }
        return null;
    }

    @Nullable
    @Contract("null, _ -> null; !null, null -> null")
    public static JSArray<JSValue> toJSArray(JSContext context, Object[] array)
    {
        if (context != null && array != null) {
            JSArray<JSValue> result = new JSArray(context, JSValue.class);

            for (Object o : array) {
                result.add(toJSValue(context, o));
            }

            return result;
        }
        return null;
    }

    @Nullable
    @Contract("null, _ -> null; !null, null -> null")
    public static JSArray<JSValue> toJSArray(JSContext context, JSONArray json)
    {
        if (context != null && json != null) {

            JSArray<JSValue> result = new JSArray(context, JSValue.class);

            for (int i = 0; i < json.length(); i++) {

                result.add(toJSValue(context, json.opt(i)));
            }

            return result;
        }
        return null;
    }

    @Nullable
    @Contract("null, _ -> null; !null, null -> null")
    public static JSObject toJSObject(JSContext context, Map<String, ?> map)
    {
        if (context != null && map != null) {
            JSObject result = new JSObject(context);

            for (String key : map.keySet()) {
                result.property(key, toJSValue(context, map.get(key)));
            }

            return result;
        }
        return null;
    }

    @Nullable
    @Contract("null, _ -> null; !null, null -> null")
    public static JSObject toJSObject(JSContext context, JSONObject json)
    {
        if (context != null && json != null) {

            JSObject result = new JSObject(context);

            Iterator<String> iter = json.keys();
            while (iter.hasNext()) {

                String key = iter.next();
                result.property(key, toJSValue(context, json.opt(key)));
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
