package com.example.brightness;

import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.provider.Settings;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class MainActivity extends PreferenceActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.brightness);

    }
    
    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
        SeekBarPreference mBrightness = (SeekBarPreference) findPreference("brightness");
    }
    
    @Override
    protected void onPause() {
        // TODO Auto-generated method stub
    	SeekBarPreference mBrightness = (SeekBarPreference) findPreference("brightness");
        super.onPause();
        
    }
    
    /**
     * 保存当前的屏幕亮度值，并使之生效
     */
    private void setScreenBrightness(int paramInt) {
        Window localWindow =getWindow();
        WindowManager.LayoutParams localLayoutParams = localWindow
                .getAttributes();
        float f = paramInt / 255.0F;
        localLayoutParams.screenBrightness = f;
        localWindow.setAttributes(localLayoutParams);
    }
   
}
