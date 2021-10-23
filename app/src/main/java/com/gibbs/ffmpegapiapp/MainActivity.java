package com.gibbs.ffmpegapiapp;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.gibbs.ffmpegapi.Resampler;

import java.nio.ByteBuffer;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        Resampler resampler = new Resampler(8000, 2, 2,
                16000, 2, 2);
        ByteBuffer byteBuffer1 = ByteBuffer.allocateDirect(160);
        byte[] sound = new byte[160];
        for (int i = 0; i < 160; i++) {
            sound[i] = (byte) i;
        }
        byteBuffer1 = byteBuffer1.put(sound);
        ByteBuffer byteBuffer2 = ByteBuffer.allocateDirect(320);
        int sample = resampler.resample(byteBuffer2, 80, byteBuffer1, 80);
        resampler.release();
        tv.setText("sample = " + Arrays.toString(byteBuffer2.array()));
    }
}