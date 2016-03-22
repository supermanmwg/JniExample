#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include "com_jniexample_MainActivity.h"

#define DEBUG_BUILD
#ifdef DEBUG_BUILD
#define debug(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "---jni---", fmt,  ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

static char package_path[] = "com/jniexample/";

JNIEXPORT void JNICALL Java_com_jniexample_MainActivity_helloWorld
        (JNIEnv *env, jobject this, jstring string) {

    /**
     * jboolean 是一个char;
     * typedef unsigned char jboolean;
     **/
    jboolean is_copy;
    //jstring 转化成 char*
    char *utf_string = (*env)->GetStringUTFChars(env, string, &is_copy);
    debug("hello from %s", utf_string);
    if (is_copy) {
        debug("is copied %d", is_copy);
    } else {
        debug("is not copied");
    }

    //使用完别忘了释放
    (*env)->ReleaseStringUTFChars(env, string, utf_string);

    if (NULL == utf_string) {
        debug("utf string pointer is null");
    } else {
        //utf string 显示是乱码，所以调用ReleaseStringUTFChars之后，要对utf_string 设置为NULL
        debug("utf string pointer is not null");
        debug("utf string is %s", utf_string);
        utf_string = NULL;
    }

    //this就是MainActivity的一个实例化的对象,通过this获得MainActivity的class，再通过反射调用MainActivity的静态方法test（）
    jclass clazz = (*env)->GetObjectClass(env, this);
    jmethodID id_test = (*env)->GetStaticMethodID(env, clazz, "test", "()V");  //静态方法
    (*env)->CallStaticVoidMethod(env, clazz, id_test);

    jmethodID id_haha = (*env)->GetMethodID(env, clazz, "haha", "(Ljava/lang/String;)V");  //普通方法
    //char* 转化成 jstring
    jstring message = (*env)->NewStringUTF(env, "mwg");
    // (*env)->CallVoidMethod(env, this, id_haha, "mwg");  //不能直接传字符串，会引起错误
    (*env)->CallVoidMethod(env, this, id_haha, message);


    jmethodID int_test = (*env)->GetMethodID(env, clazz, "intTest",
                                             "(ILjava/lang/String;)V");  //如果不加“；”也会报错
    jint num1 = 5;
    (*env)->CallVoidMethod(env, this, int_test, num1, message);
    (*env)->DeleteLocalRef(env, message);  //删除message本地引用，不然会引起内存泄露

    jmethodID int_only = (*env)->GetMethodID(env, clazz, "intOnly",
                                             "(I)V"); //I不能加；String 和Object必须加
    jint num2 = 6;
    (*env)->CallVoidMethod(env, this, int_only, num2);

    jmethodID object_only = (*env)->GetMethodID(env, clazz, "objectOnly",
                                                "(Ljava/lang/Object;)V"); //必须加；不然会报错
    (*env)->CallVoidMethod(env, this, object_only, this);

    //传递int数组
    jmethodID int_array_only = (*env)->GetMethodID(env, clazz, "intArrayOnly", "([I)V");
    jintArray testIntArray = (*env)->NewIntArray(env, 10);
    jint test[10];
    int i = 0;
    for (i = 0; i < 10; ++i) {
        *(test + i) = i + 100;
    }
    (*env)->SetIntArrayRegion(env, testIntArray, 0, 10, &test);
    (*env)->CallVoidMethod(env, this, int_array_only, testIntArray);
    (*env)->DeleteLocalRef(env, testIntArray);

    //传递字符串数组
    jmethodID string_array_only = (*env)->GetMethodID(env, clazz, "stringArrayOnly",
                                                      "([Ljava/lang/Object;)V");
    jclass string_class = (*env)->FindClass(env, "java/lang/String");
    jstring string_item = (*env)->NewStringUTF(env, "mwg");
    jobjectArray string_array = (*env)->NewObjectArray(env, 7, string_class, string_item);
    (*env)->CallVoidMethod(env, this, string_array_only, string_array);
    (*env)->DeleteLocalRef(env, string_item);
    (*env)->DeleteLocalRef(env, string_array);

    //传递Student对象
    jmethodID student_array_only = (*env)->GetMethodID(env, clazz, "studentArrayOnly",
                                                       "([Lcom/jniexample/utils/Student;)V");
    jclass student_class = (*env)->FindClass(env, "com/jniexample/utils/Student");
    jmethodID student_id = (*env)->GetMethodID(env, student_class, "<init>",
                                               "(Ljava/lang/String;Ljava/lang/String;)V");
    jstring name = (*env)->NewStringUTF(env, "mwg");
    jstring sex = (*env)->NewStringUTF(env, "male");
    jobject student = (*env)->NewObject(env, student_class, student_id, name, sex);
    jobjectArray student_array = (*env)->NewObjectArray(env, 6, student_class, student);
    (*env)->CallVoidMethod(env, this, student_array_only, student_array);
    (*env)->DeleteLocalRef(env, name);
    (*env)->DeleteLocalRef(env, sex);
    (*env)->DeleteLocalRef(env, student);
    (*env)->DeleteLocalRef(env, student_array);


    //获得对象属性值
    jfieldID tag_id = (*env)->GetFieldID(env, clazz, "name", "Ljava/lang/String;");  //必须加“;”
    jstring haha_string = (jstring) (*env)->GetObjectField(env, this, tag_id);

    //普通属性
    char *tag_array = (*env)->GetStringUTFChars(env, haha_string, NULL);
    debug("haha is %s", tag_array);

    //静态属性，必须用以下方法，不然会报错
    jfieldID haha_id = (*env)->GetStaticFieldID(env, clazz, "TAG", "Ljava/lang/String;");
    jstring tag_string = (*env)->GetStaticObjectField(env, clazz, haha_id);

    char *haha_array = (*env)->GetStringUTFChars(env, tag_string, NULL);
    debug("tag is %s", haha_array);
}