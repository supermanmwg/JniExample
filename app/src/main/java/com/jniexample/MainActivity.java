package com.jniexample;

import android.os.Bundle;
import android.util.Log;

import com.example.weiguangmeng.activitytest.R;
import com.jniexample.base.BaseActivity;
import com.jniexample.utils.Student;

public class MainActivity extends BaseActivity {
    private static String TAG = "MainActivity";
    private String name = "haha";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        helloWorld("mwg");
    }

    public native void helloWorld(String name);

    static {
        System.loadLibrary("hello-jni");
    }

    public static void test(){
        Log.d(TAG, "have a test");
    }

    public void haha(String name) {
        Log.d(TAG, name + " is very happy!");
    }

    public void intTest(int num, String name) {
        Log.d(TAG, "num is " + num + ", name is " + name);
    }

    public void intOnly(int num) {
        Log.d(TAG, "int only is " + num);
    }

    public void objectOnly(Object o) {
        Log.d(TAG, "object is " + o.toString());
    }

    public void intArrayOnly(int[] array) {
        Log.d(TAG, "array[0] is " + array[0] + ", array length is " + array.length);
    }

    public void stringArrayOnly(Object[] array) {
        Log.d(TAG, "array[0] is " + array[0].toString() + ", array length is " + array.length);
    }

    public void studentArrayOnly(Student[] students) {
        for(int i = 0; i < students.length; i++) {
            Log.d(TAG, "student name is " + students[i].getName() + ", sex is " + students[i].getSex());
        }
    }
}
