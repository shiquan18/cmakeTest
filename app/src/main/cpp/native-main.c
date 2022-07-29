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
#define printf(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


extern void mainC() {
    LOGI("c user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    LOGD("c user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
    LOGE("c user info----name:%s, age:%d, sex:%s.", "xxx", 18, "男");
}