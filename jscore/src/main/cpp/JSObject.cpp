#include <JavaScriptCore/JavaScript.h>
#include "JSFunction.h"
#include "JSUtils.h"


NATIVE(JSObject,jlong,make) (PARAMS, jlong ctx, jlong data) {
    JSObjectRef value = JSObjectMake((JSContextRef)ctx, (JSClassRef) NULL, (void*)data);
    JSValueProtect((JSContextRef) ctx, value);
    return (long)value;
}

NATIVE(JSObject,jlong,makeInstance) (PARAMS, jlong ctx) {
    JSInstance *instance = new JSInstance(env, thiz, (JSContextRef)ctx);
    return instance->getObjRef();
}

NATIVE(JSObject,jlong,makeFunctionWithCallback) (PARAMS, jlong ctx, jlong name) {
    JSFunction *function = new JSFunction(env, thiz, (JSContextRef)ctx,
                                          (JSStringRef)name);
    return function->getObjRef();
}

NATIVE(JSObject,jobject,makeArray) (PARAMS, jlong ctx, jlongArray args) {
    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(args);
    jlong *values = env->GetLongArrayElements(args, 0);
    JSValueRef* elements = new JSValueRef[len];
    for (i=0; i<len; i++) {
        elements[i] = (JSValueRef) values[i];
    }
    env->ReleaseLongArrayElements(args, values, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSObjectRef objRef = JSObjectMakeArray((JSContextRef)ctx, (size_t)len, (len==0)?NULL:elements,
                                           &exception);
    JSValueProtect((JSContextRef) ctx, objRef);

    env->SetLongField( out, fid, (jlong)objRef );

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] elements;
    return out;
}

NATIVE(JSObject,jobject,makeDate) (PARAMS, jlong ctx, jlongArray args) {
    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(args);
    jlong *values = env->GetLongArrayElements(args, 0);
    JSValueRef* elements = new JSValueRef[len];
    for (i=0; i<len; i++) {
        elements[i] = (JSValueRef) values[i];
    }
    env->ReleaseLongArrayElements(args, values, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSObjectRef objRef = JSObjectMakeDate((JSContextRef)ctx, (size_t)len, (len==0)?NULL:elements,
                                          &exception);
    JSValueProtect((JSContextRef) ctx, objRef);
    env->SetLongField( out, fid, (jlong) objRef );

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] elements;
    return out;
}

NATIVE(JSObject,jobject,makeError) (PARAMS, jlong ctx, jlongArray args) {
    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(args);
    jlong *values = env->GetLongArrayElements(args, 0);
    JSValueRef* elements = new JSValueRef[len];
    for (i=0; i<len; i++) {
        elements[i] = (JSValueRef) values[i];
    }
    env->ReleaseLongArrayElements(args, values, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSObjectRef objRef = JSObjectMakeError((JSContextRef)ctx, (size_t)len, (len==0)?NULL:elements,
                                           &exception);
    JSValueProtect((JSContextRef) ctx, objRef);
    env->SetLongField( out, fid, (long) objRef );

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] elements;
    return out;
}

NATIVE(JSObject,jobject,makeRegExp) (PARAMS, jlong ctx, jlongArray args) {
    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(args);
    jlong *values = env->GetLongArrayElements(args, 0);
    JSValueRef* elements = new JSValueRef[len];
    for (i=0; i<len; i++) {
        elements[i] = (JSValueRef) values[i];
    }
    env->ReleaseLongArrayElements(args, values, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSObjectRef objRef = JSObjectMakeRegExp((JSContextRef)ctx, (size_t)len, (len==0)?NULL:elements,
                                            &exception);
    JSValueProtect((JSContextRef) ctx, objRef);
    env->SetLongField( out, fid, (long) objRef );

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] elements;
    return out;
}

NATIVE(JSObject,jobject,makeFunction) (PARAMS, jlong ctx, jlong name,
                                       jlongArray parameterNames, jlong body, jlong sourceURL, jint startingLineNumber) {

    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(parameterNames);
    jlong *parameters = env->GetLongArrayElements(parameterNames, 0);
    JSStringRef* parameterNameArr = new JSStringRef[len];
    for (i=0; i<len; i++) {
        parameterNameArr[i] = (JSStringRef) parameters[i];
    }
    env->ReleaseLongArrayElements(parameterNames, parameters, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSObjectRef objref = JSObjectMakeFunction(
            (JSContextRef)ctx,
            (JSStringRef)name,
            (unsigned)len,
            (len==0)?NULL:parameterNameArr,
            (JSStringRef) body,
            (JSStringRef) sourceURL,
            (int)startingLineNumber,
            &exception);
    JSValueProtect((JSContextRef) ctx, objref);
    env->SetLongField( out, fid, (long)objref);

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] parameterNameArr;
    return out;
}

NATIVE(JSObject,jlong,getPrototype) (PARAMS, jlong ctx, jlong object) {
    JSValueRef value = JSObjectGetPrototype((JSContextRef)ctx, (JSObjectRef)object);
    JSValueProtect((JSContextRef)ctx, value);
    return (long)value;
}

NATIVE(JSObject,void,setPrototype) (PARAMS, jlong ctx, jlong object, jlong value) {
    JSObjectSetPrototype((JSContextRef)ctx, (JSObjectRef)object, (JSValueRef)value);
}

NATIVE(JSObject,jboolean,hasProperty) (PARAMS, jlong ctx, jlong object, jlong propertyName) {
    return JSObjectHasProperty((JSContextRef)ctx, (JSObjectRef) object, (JSStringRef)propertyName);
}

NATIVE(JSObject,jobject,getProperty) (PARAMS, jlong ctx, jlong object,
                                      jlong propertyName) {

    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSValueRef value = JSObjectGetProperty((JSContextRef)ctx, (JSObjectRef)object, (JSStringRef)propertyName,
                                           &exception);
    JSValueProtect((JSContextRef) ctx, value);

    env->SetLongField( out, fid, (long)value);

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    return out;
}

NATIVE(JSObject,jobject,setProperty) (PARAMS, jlong ctx, jlong object, jlong propertyName,
                                      jlong value, jint attributes) {

    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    JSObjectSetProperty((JSContextRef)ctx, (JSObjectRef) object, (JSStringRef) propertyName,
                        (JSValueRef)value, (JSPropertyAttributes)attributes, &exception);

    jfieldID fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    return out;
}

NATIVE(JSObject,jobject,deleteProperty) (PARAMS, jlong ctx, jlong object,
                                         jlong propertyName) {

    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret ,"bool", "Z");

    bool bval = (bool) JSObjectDeleteProperty((JSContextRef)ctx, (JSObjectRef) object,
                                              (JSStringRef) propertyName, &exception);

    env->SetBooleanField( out, fid, bval);

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    return out;
}

NATIVE(JSObject,jobject,getPropertyAtIndex) (PARAMS, jlong ctx, jlong object,
                                             jint propertyIndex) {

    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSValueRef value = JSObjectGetPropertyAtIndex((JSContextRef)ctx, (JSObjectRef) object,
                                                  (unsigned)propertyIndex, &exception);
    JSValueProtect((JSContextRef)ctx, value);

    env->SetLongField( out, fid, (long)value );

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    return out;
}

NATIVE(JSObject,jobject,setPropertyAtIndex) (PARAMS, jlong ctx, jlong object,
                                             jint propertyIndex, jlong value) {

    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSObjectSetPropertyAtIndex((JSContextRef)ctx, (JSObjectRef) object, (unsigned) propertyIndex,
                               (JSValueRef)value, &exception);

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);


    return out;
}

NATIVE(JSObject,jlong,getPrivate) (PARAMS, jlong object) {
    return (long) JSObjectGetPrivate((JSObjectRef) object);
}

NATIVE(JSObject,jboolean,setPrivate) (PARAMS, jlong object, jlong data) {
    return JSObjectSetPrivate((JSObjectRef) object, (void*) data);
}

NATIVE(JSObject,jboolean,isFunction) (PARAMS, jlong ctx, jlong object) {
    return (jboolean) JSObjectIsFunction((JSContextRef)ctx, (JSObjectRef) object);
}

NATIVE(JSObject,jobject,callAsFunction) (PARAMS, jlong ctx, jlong object,
                                         jlong thisObject, jlongArray args) {
    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(args);
    jlong *values = env->GetLongArrayElements(args, 0);
    JSValueRef* elements = new JSValueRef[len];
    for (i=0; i<len; i++) {
        elements[i] = (JSValueRef) values[i];
    }
    env->ReleaseLongArrayElements(args, values, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSValueRef value = JSObjectCallAsFunction((JSContextRef)ctx, (JSObjectRef) object, (JSObjectRef) thisObject,
                                              (size_t)len, (len==0)?NULL:elements, &exception);
    JSValueProtect((JSContextRef) ctx, value);

    env->SetLongField( out, fid, (long)value);

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] elements;
    return out;
}

NATIVE(JSObject,jboolean,isConstructor) (PARAMS, jlong ctx, jlong object) {
    return (jboolean) JSObjectIsConstructor((JSContextRef)ctx, (JSObjectRef)object);
}

NATIVE(JSObject,jobject,callAsConstructor) (PARAMS, jlong ctx, jlong object,
                                            jlongArray args) {

    JSValueRef exception = NULL;

    int i;
    jsize len = env->GetArrayLength(args);
    jlong *values = env->GetLongArrayElements(args, 0);
    JSValueRef* elements = new JSValueRef[len];
    for (i=0; i<len; i++) {
        elements[i] = (JSValueRef) values[i];
    }
    env->ReleaseLongArrayElements(args, values, 0);

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret,"<init>","()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret , "reference", "J");

    JSValueRef value = JSObjectCallAsConstructor((JSContextRef)ctx, (JSObjectRef) object,
                                                 (size_t)len, (len==0)?NULL:elements, &exception);
    JSValueProtect((JSContextRef) ctx, value);

    env->SetLongField( out, fid, (long)value);

    fid = env->GetFieldID(ret , "exception", "J");
    env->SetLongField( out, fid, (long) exception);

    delete [] elements;
    return out;
}

NATIVE(JSObject,jlong,copyPropertyNames) (PARAMS, jlong ctx, jlong object) {
    JSPropertyNameArrayRef ref = JSObjectCopyPropertyNames((JSContextRef)ctx, (JSObjectRef)object);
    JSPropertyNameArrayRetain(ref);
    return (long)ref;
}

NATIVE(JSObject,jlongArray,getPropertyNames) (PARAMS,jlong propertyNameArray) {
    size_t count = JSPropertyNameArrayGetCount((JSPropertyNameArrayRef)propertyNameArray);
    jlongArray retArray = env->NewLongArray(count);
    jlong* stringRefs = new jlong[count];
    for (size_t i=0; i<count; i++) {
        stringRefs[i] = (long) JSStringRetain(JSPropertyNameArrayGetNameAtIndex(
                (JSPropertyNameArrayRef)propertyNameArray, i));
    }
    env->SetLongArrayRegion(retArray,0,count,stringRefs);

    return retArray;
}

NATIVE(JSObject,void,releasePropertyNames) (PARAMS, jlong propertyNameArray) {
    JSPropertyNameArrayRelease((JSPropertyNameArrayRef)propertyNameArray);
}
