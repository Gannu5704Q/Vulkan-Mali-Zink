package com.gannu5704q.vulkanmalizink;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        TextView textView = new TextView(this);
        textView.setText("Plugin");
        textView.setPadding(32, 32, 32, 32);
        textView.setTextSize(16);
        
        setContentView(textView);
    }
}
