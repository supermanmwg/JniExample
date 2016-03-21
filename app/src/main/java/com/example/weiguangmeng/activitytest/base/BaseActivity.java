package com.example.weiguangmeng.activitytest.base;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.example.weiguangmeng.activitytest.utils.Logger;

/**
 * Created by weiguangmeng on 16/1/28.
 */
public class BaseActivity extends AppCompatActivity {

    public Logger logger = Logger.createLogger(getClass().getSimpleName());

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        logger.log("onCreate");
    }

    @Override
    protected void onStart() {
        super.onStart();
        logger.log("onStart");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        logger.log("onRestart");
    }

    @Override
    protected void onResume() {
        super.onResume();
        logger.log("onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        logger.log("onPause");
    }

    @Override
    protected void onStop() {
        super.onStop();
        logger.log("onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        logger.log("onDestroy");
    }
}
