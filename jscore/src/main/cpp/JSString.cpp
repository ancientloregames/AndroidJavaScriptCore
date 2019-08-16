
#include <JavaScriptCore/JSStringRef.h>
#include "JSUtils.h"

NATIVE(JSValue_00024JSString,jlong,createWithCharacters) (PARAMS, jstring str)
{
const jchar *chars = env->GetStringChars(str, NULL);
JSStringRef string = JSStringRetain(JSStringCreateWithCharacters(chars,
                                                                 env->GetStringLength(str)));
env->ReleaseStringChars(str,chars);
return (long)string;
}

NATIVE(JSValue_00024JSString,jlong,createWithUTF8CString) (PARAMS, jstring str)
{
const char *string = env->GetStringUTFChars(str, NULL);
JSStringRef ret = JSStringRetain(JSStringCreateWithUTF8CString(string));
env->ReleaseStringUTFChars(str, string);
return (long)ret;
}

NATIVE(JSValue_00024JSString,jlong,retain) (PARAMS, jlong strRef) {
return (jlong) JSStringRetain((JSStringRef)strRef);
}

NATIVE(JSValue_00024JSString,void,release) (PARAMS, jlong stringRef) {
JSStringRelease((JSStringRef)stringRef);
}

NATIVE(JSValue_00024JSString,jint,getLength) (PARAMS, jlong stringRef) {
return (jint) JSStringGetLength((JSStringRef)stringRef);
}

NATIVE(JSValue_00024JSString,jstring,toString) (PARAMS, jlong stringRef) {
char *buffer = new char[JSStringGetMaximumUTF8CStringSize((JSStringRef)stringRef)+1];
JSStringGetUTF8CString((JSStringRef)stringRef, buffer,
JSStringGetMaximumUTF8CStringSize((JSStringRef)stringRef)+1);
jstring ret = env->NewStringUTF(buffer);
delete buffer;
return ret;
}

NATIVE(JSValue_00024JSString,jint,getMaximumUTF8CStringSize) (PARAMS, jlong stringRef) {
return (jint) JSStringGetMaximumUTF8CStringSize((JSStringRef)stringRef);
}

NATIVE(JSValue_00024JSString,jboolean,isEqual) (PARAMS, jlong a, jlong b) {
return (jboolean) JSStringIsEqual((JSStringRef)a, (JSStringRef)b);
}

NATIVE(JSValue_00024JSString,jboolean,isEqualToUTF8CString) (PARAMS, jlong a, jstring b) {
const char *string = env->GetStringUTFChars(b, NULL);
jboolean ret = JSStringIsEqualToUTF8CString((JSStringRef)a, string);
env->ReleaseStringUTFChars(b, string);
return ret;
}


