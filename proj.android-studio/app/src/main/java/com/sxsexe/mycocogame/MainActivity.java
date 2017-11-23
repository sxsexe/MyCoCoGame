package com.sxsexe.mycocogame;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import org.cocos2dx.cpp.PintuMainActivity;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnPintu = (Button) findViewById(R.id.btn_pintu);
        if(btnPintu != null) {
            btnPintu.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent intent = new Intent(MainActivity.this, PintuMainActivity.class);
                    startActivity(intent);
                }
            });
        }


    }
}
