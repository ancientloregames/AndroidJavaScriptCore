#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <android/log.h>
#include <JavaScriptCore/JSBase.h>
#include <JavaScriptCore/JavaScript.h>
#include "JSUtils.h"

static int pfd[2];
static pthread_t thr;

static void *thread_func(void *) {
    ssize_t rdsz;
    char buf[128];
    while ((rdsz = read(pfd[0], buf, sizeof buf - 1)) > 0) {
        if (buf[rdsz - 1] == '\n') --rdsz;
        buf[rdsz - 1] = 0;  /* add null-terminator */
//        __android_log_write(ANDROID_LOG_DEBUG, "JavaScriptCore", buf);
    }
    return 0;
}

NATIVE(JSContext, void, staticInit)(PARAMS) {
/* make stdout line-buffered and stderr unbuffered */
    setvbuf(stdout, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);

/* create the pipe and redirect stdout and stderr */
    pipe(pfd);
    dup2(pfd[1], 1);
    dup2(pfd[1], 2);

/* spawn the logging thread */
    if (pthread_create(&thr, 0, thread_func, 0) == -1)
        return; // fail silently
    pthread_detach(thr);
}

NATIVE(JSContextGroup, jlong, create)(PARAMS) {
    JSContextGroupRef group = JSContextGroupCreate();
    JSContextGroupRetain(group);
    return (long) group;
}

NATIVE(JSContextGroup, jlong, retain)(PARAMS, jlong group) {
    return (long) JSContextGroupRetain((JSContextGroupRef) group);
}

NATIVE(JSContextGroup, void, release)(PARAMS, jlong group) {
    JSContextGroupRelease((JSContextGroupRef) group);
}

NATIVE(JSContext, jlong, create)(PARAMS) {
    JSGlobalContextRef ref = JSGlobalContextCreate((JSClassRef) NULL);
//JSGlobalContextRetain(ref);
    return (long) ref;
}

NATIVE(JSContext, jlong, createInGroup)(PARAMS, jlong group) {
    JSGlobalContextRef ref = JSGlobalContextCreateInGroup((JSContextGroupRef) group,
                                                          (JSClassRef) NULL);
//JSGlobalContextRetain(ref);
    return (long) ref;
}

NATIVE(JSContext, jlong, retain)(PARAMS, jlong ctx) {
    return (jlong) JSGlobalContextRetain((JSGlobalContextRef) ctx);
}

NATIVE(JSContext, void, release)(PARAMS, jlong ctx) {
    JSGlobalContextRelease((JSGlobalContextRef) ctx);
}

NATIVE(JSContext, jlong, getGlobalObject)(PARAMS, jlong ctx) {
    JSObjectRef ref = JSContextGetGlobalObject((JSContextRef) ctx);
    JSValueProtect((JSContextRef) ctx, ref);
    return (long) ref;
}

NATIVE(JSContext, jlong, getGroup)(PARAMS, jlong ctx) {
    JSContextGroupRef group = JSContextGetGroup((JSContextRef) ctx);
    JSContextGroupRetain(group);
    return (long) group;
}

NATIVE(JSContext, jobject, evaluateScript)(PARAMS, jlong ctx, jlong script,
                                           jlong thisObject, jlong sourceURL, jint startingLineNumber)
{
    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret, "<init>", "()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret, "reference", "J");

    JSValueRef value = JSEvaluateScript(
            (JSContextRef) ctx,
            (JSStringRef) script,
            (JSObjectRef) thisObject,
            (JSStringRef) sourceURL,
            startingLineNumber,
            &exception);
    JSValueProtect((JSContextRef) ctx, value);

    env->SetLongField(out, fid, (long) value);

    fid = env->GetFieldID(ret, "exception", "J");
    env->SetLongField(out, fid, (jlong) exception);

    return out;
}

NATIVE(JSContext, jobject, checkScriptSyntax)(PARAMS, jlong ctx, jlong script,
                                              jlong sourceURL, jint startingLineNumber) {

    JSValueRef exception = NULL;

    jclass ret = env->FindClass("com/ancientlore/jscore/JSValue$JNIReturnObject");
    jmethodID cid = env->GetMethodID(ret, "<init>", "()V");
    jobject out = env->NewObject(ret, cid);

    jfieldID fid = env->GetFieldID(ret, "reference", "J");
    bool value = JSCheckScriptSyntax(
            (JSContextRef) ctx,
            (JSStringRef) script,
            (JSStringRef) sourceURL,
            startingLineNumber,
            &exception);
    env->SetBooleanField(out, fid, value);

    fid = env->GetFieldID(ret, "exception", "J");
    env->SetLongField(out, fid, (jlong) exception);

    return out;
}

NATIVE(JSContext, void, garbageCollect)(PARAMS, jlong ctx) {
    JSGarbageCollect((JSContextRef) ctx);
}

