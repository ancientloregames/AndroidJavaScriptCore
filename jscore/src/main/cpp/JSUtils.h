#ifndef JNI_JSUTILS_H
#define JNI_JSUTILS_H

#include <stdlib.h>
#include <jni.h>
#include <android/log.h>


#define NATIVE(javaClassName, returnType, methodName) extern "C" JNIEXPORT returnType JNICALL Java_com_ancientlore_jscore_##javaClassName##_##methodName
#define PARAMS JNIEnv *env, jobject thiz

#endif