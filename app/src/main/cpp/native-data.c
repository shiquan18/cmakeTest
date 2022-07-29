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

void main();

void test1();

void test2();

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

void JNICALL
Java_com_example_myapplicationcmake_MainActivity_JniMain(JNIEnv *env, jobject thiz) {
    LOGE("Main=============================================%s,", "start");
    main();
    LOGE("Main=============================================%s,", "end");
}

void main() {
    test1();
//    test2();
}

void test2() {
    int num[50], n, *p, j, loop, i, m, k;
    printf("请输入这一圈人的数量:\n");
//    scanf("%d", &n);
    n = 5;
    p = num;
    //开始给这些人编号
    for (j = 0; j < n; j++) {
        *(p + j) = j + 1;
    }
    i = 0;//i用于计数,即让指针后移
    m = 0;//m记录退出圈子的人数
    k = 0;//k报数1,2,3
    while (m < n - 1)//当退出的人数不大于总人数时，即留下的人数至少是一个人
        //这句不能写成m<n,因为假设有8人，当退出了6人时，此时还是进行人数退出，即m++，
        //这时是7<8，剩下的一个人自己喊1，2,3那么他也就退出了，将不会有输出
    {
        if (*(p + i) != 0)//如果这个人的头上编号不是0就开始报数加1，这里采用的方法是报数为3的人头上编号重置为0
        {
            k++;
        }
        if (k == 3) {
            k = 0;    //报数清零，即下一个人从1开始报数
            *(p + i) = 0;//将报数为3的人编号重置为0
            m++;    //退出人数加1
        }
        i++;      //指针后移
        if (i == n)//这句很关键，如果到了队尾，就要使指针重新指向对头
            //并且它只能放在i++后面，因为只有i++了才有可能i==n
        {
            i = 0;
        }


    }
    printf("现在剩下的人是:");
    for (loop = 0; loop < n; loop++) {
        if (num[loop] != 0) {
            printf("%2d号\n", num[loop]);
        }
    }

}

void test1() {
    int a, b;
    a = 234;
    b = ~a;
    printf("a 的按位取反值为（十进制） %d \n", b);
    a = ~a;
    printf("a 的按位取反值为（十六进制） %x \n", a);
}


