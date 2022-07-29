#include <jni.h>
#include <string.h>
#include  <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include "jni.h"
//#include "native-main.c"

#define  TAG    "MainActivity"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define printf(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

//extern void mainC();

void mainJ();

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
    mainJ();
//    mainC();
    LOGE("Main=============================================%s,", "end");
}

JNIEXPORT int maxS(int x, int y) {
    return x > y ? x : y;
}

JNIEXPORT void test0_1() {
    /* p 是函数指针 */
    int (*p)(int, int) = &maxS; // &可以省略
    int a = 15, b = 11, c = 12, d = 13;
    printf("请输入三个数字:");
//    scanf("%d %d %d", &a, &b, &c);
    /* 与直接调用函数等价，d = maxS(maxS(a, b), c) */
    d = p(p(a, b), c);
    printf("最大的数字是: %d\n", d);
}

JNIEXPORT void test0_2() {
    int var = 20;   /* 实际变量的声明 */
    int *ip;        /* 指针变量的声明 */
    ip = &var;  /* 在指针变量中存储 var 的地址 */
    printf("var 变量的地址: %p\n", &var);
/* 在指针变量中存储的地址 */
    printf("ip 变量存储的地址: %p\n", ip);
/* 使用指针访问值 */
    printf("*ip 变量的值: %d\n", *ip);
}
// 回调函数
JNIEXPORT void test5_populate_array(int *array, size_t arraySize, int (*getNextValue)(void)) {
    for (size_t i = 0; i < arraySize; i++)
        array[i] = getNextValue();
}

// 获取随机值
JNIEXPORT int test5_getNextRandomValue(void) {
    return rand();
}

JNIEXPORT void test0_3() {
    int myarray[10];
    /* test5_getNextRandomValue 不能加括号，否则无法编译，因为加上括号之后相当于传入此参数时传入了 int , 而不是函数指针*/
    test5_populate_array(myarray, 10, test5_getNextRandomValue);
    for (int i = 0; i < 10; i++) {
        printf("%d ", myarray[i]);
    }
    printf("\n");
}

JNIEXPORT void test2() {
    const int MAX = 3;
    int var[] = {10, 100, 200};
    int i, *ptr;
    /* 指针中最后一个元素的地址 */
    ptr = &var[MAX - 1];
    for (i = MAX; i > 0; i--) {
        printf("存储地址：var[%d] = %p\n", i - 1, ptr);
        printf("存储值：var[%d] = %d\n", i - 1, *ptr);
        /* 指向下一个位置 */
        ptr--;
    }
}


JNIEXPORT void test1() {
    const int MAX = 3;
    int var[] = {10, 100, 200};
    int i, *ptr;
    /* 指针中的数组地址 */
    ptr = var;
    for (i = 0; i < MAX; i++) {
        printf("存储地址：var[%d] = %p\n", i, ptr);
        printf("存储值：var[%d] = %d\n", i, *ptr);
        /* 指向下一个位置 */
        ptr++;
    }
}

JNIEXPORT void test2_1() {
    const int MAX = 3;
    int var[] = {10, 100, 200};
    int i, *ptr;
    /* 指针中第一个元素的地址 */
    ptr = var;
    i = 0;
    while (ptr <= &var[MAX - 1]) {
        printf("存储地址：var[%d] = %p\n", i, ptr);
        printf("存储值：var[%d] = %d\n", i, *ptr);
        /* 指向上一个位置 */
        ptr++;
        i++;
    }
}

const int MAX = 3;

JNIEXPORT void test3() {
    int var[] = {10, 100, 200};
    int i;
    for (i = 0; i < MAX; i++) {
        printf("Value of var[%d] = %d\n", i, var[i]);
    }
}

JNIEXPORT void test3_1() {
    int var[] = {10, 100, 200};
    int i, *ptr[MAX];

    for (i = 0; i < MAX; i++) {
        ptr[i] = &var[i]; /* 赋值为整数的地址 */
    }
    for (i = 0; i < MAX; i++) {
        printf("Value of var[%d] = %d\n", i, *ptr[i]);
    }
}

JNIEXPORT void test3_2() {
    const int MAX = 4;
    const char *names[] = {
            "Zara Ali",
            "Hina Ali",
            "Nuha Ali",
            "Sara Ali",
    };
    int i = 0;

    for (i = 0; i < MAX; i++) {
        printf("Value of names[%d] = %s\n", i, names[i]);
    }
}

//JNIEXPORT void test() {}
void mainJ() {
//    test0_1();
//    test0_2();
//    test0_3();
//    test1();
//    test2();
//    test2_1();
    test3();
//    test3_1();
//    test3_2();
}




