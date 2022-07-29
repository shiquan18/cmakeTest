#include <jni.h>
#include <string>
#include <iostream>
#include  <android/log.h>

#define  TAG    "MainActivity"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplicationcmake_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplicationcmake_MainActivity_stringFromJNI2(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C2";
    LOGI("user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    LOGD("user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    LOGE("user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    return env->NewStringUTF(hello.c_str());
}