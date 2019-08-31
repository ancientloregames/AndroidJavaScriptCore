package com.ancientlore.jscore;

import androidx.annotation.Nullable;


public final class JSProperty<T> extends JSValue
{
    private final Class type;

    public JSProperty(JSContext context, Class type)
    {
        super(context);
        this.type = type;
    }

    public JSProperty(JSContext context, T value)
    {
        super(context, value);
        type = value.getClass();
    }

    public void set(T value)
    {
        setValue(value);
    }

    /**
     * @return the current property value. Or null, if:
     * 1. the generic type is incompatible with the type of this property in JS
     * 2. property in JS is either null, or undefined
     */
    @Nullable
    public T get()
    {
        if (isNull() || isUndefined())
            return null;

        Object value = null;
        if (isNumber())
        {
            if (type == Integer.class)
                value = toNumber().intValue();
            else if (type == Float.class)
                value = toNumber().floatValue();
            else if (type == Double.class)
                value = toNumber();
            else if (type == Long.class)
                value = toNumber().longValue();
            else if (type == Short.class)
                value = toNumber().shortValue();
        }
        else if (type == Boolean.class && isBoolean())
            value = toBoolean();
        else if (type == String.class && isString())
            value = toString();
        else if (type == JSObject.class && isObject())
            value = toObject();
        else if (type == JSFunction.class && isFunction())
            value = toFunction();
        else if (type == JSArray.class && isArray())
            value = toJSArray();

        return (T) value;
    }
}
