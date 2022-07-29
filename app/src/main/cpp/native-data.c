#include <jni.h>
#include <string.h>
#include  <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include "jni.h"

#define  TAG    "MainActivity"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


JNIEXPORT jstring JNICALL
Java_com_example_myapplicationcmake_MainActivity_stringFromJNI3(JNIEnv *env, jobject thiz) {
    LOGI("c user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    LOGD("c user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    LOGE("c user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    return (*env)->NewStringUTF(env, "c jni stringFromJNI3 ");
}

//获取非静态字段值 和 修改非静态字段值
JNIEXPORT jstring JNICALL
Java_com_example_myapplicationcmake_MainActivity_accessField(JNIEnv *env, jobject thiz) {
    jclass cls = (*env)->GetObjectClass(env, thiz);//得到class
    jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");//jfieldID
    jstring jstr = (*env)->GetObjectField(env, thiz, fid);//获取字段值
    const char *str = (*env)->GetStringUTFChars(env, jstr, 0);//jstring转为 C/C++字符串
    LOGE("str:%s,", str);
    char text[50] = "super ";//拼接字符串
    strcat(text, str);
    jstr = (*env)->NewStringUTF(env, text);//从C字符串转为jstring
    (*env)->SetObjectField(env, thiz, fid, jstr);//修改key的属性
    return jstr;
}

JNIEXPORT jint JNICALL
Java_com_example_myapplicationcmake_MainActivity_accessStaticField(JNIEnv *env, jobject obj) {
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, cls, "count", "I");
    jint count = (*env)->GetIntField(env, obj, fid);
    LOGE("count:%d,", count);
    count += 10;
    LOGE("count:%d,", count);
    (*env)->SetIntField(env, obj, fid, count);//设置值==121
}

//c 调用 java方法并传参数
JNIEXPORT void JNICALL
Java_com_example_myapplicationcmake_MainActivity_accessMethod(JNIEnv *env, jobject obj) {
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "genRandomInt", "(I)I");
    int count = 2000;
    jint random = (*env)->CallIntMethod(env, obj, mid, count);
    //int转为字符串
    char text[50];
    LOGE("random int:%d,", random);
    sprintf(text, "%d", random);
    LOGE("random str:%s,", text);

}

JNIEXPORT void JNICALL
Java_com_example_myapplicationcmake_MainActivity_JniMain(JNIEnv *env, jobject thiz) {
    LOGE("JniMain=%s,", "JniMain start");


    LOGE("JniMain=%s,", "JniMain end");
}