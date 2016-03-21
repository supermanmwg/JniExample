package com.example.weiguangmeng.activitytest.utils;

import android.util.Log;

/**
 * Created by weiguangmeng on 16/1/28.
 */
public class Logger {

    private String mTag = null;

    public Logger(String tag) {
        mTag = tag;
    }

    public void log(String message) {
        Log.d(mTag, message);
    }

    public static Logger createLogger(String tag) {
        return new Logger(tag);
    }
}
