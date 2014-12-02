package com.example.brightness;

import android.app.Activity;
import android.content.Context;
import android.preference.DialogPreference;
import android.provider.Settings;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.SeekBar.OnSeekBarChangeListener;

public class SeekBarPreference extends DialogPreference 
implements OnSeekBarChangeListener{

    private SeekBar mSeekBar;
    private int progress;
    public SeekBarPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
        // TODO Auto-generated constructor stub
    }

    @Override
    protected void onBindDialogView(View view) {
        // TODO Auto-generated method stub
        super.onBindDialogView(view);
        mSeekBar = (SeekBar)view.findViewById(R.id.seekBar1);
        
        mSeekBar.setOnSeekBarChangeListener(this);
        
        Log.i("onBindDialogView", "======getScreenBrightness========"+getScreenBrightness()/12.75);
        
        mSeekBar.setProgress((int) (getScreenBrightness()/12.75));
        
    }

    public int getProgress()
    {
        return progress;
    }
    
    @Override
    protected void onDialogClosed(boolean positiveResult) {
        // TODO Auto-generated method stub
       if(positiveResult)
       {
           Log.i("Dialog closed", "You click positive button"); 
           progress = mSeekBar.getProgress();
           setScreenBrightness(getContext(), (int) (progress*12.75));
       }
       else{
           Log.i("Dialog closed", "You click negetive button"); 
       }
       
    }
    
    @Override
    public void onProgressChanged(SeekBar seekBar, int progress,
            boolean fromUser) {
        // TODO Auto-generated method stub
        saveScreenBrightness((int) (seekBar.getProgress()*12.75));
        setScreenBrightness(getContext(), (int) (seekBar.getProgress()*12.75));
        Log.i("onProgressChanged", "===========saveScreenBrightness=========="+seekBar.getProgress()*12.75);
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
        // TODO Auto-generated method stub
        
    }
    
    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        // TODO Auto-generated method stub
      
    }
    
    /**
     * 获取当前屏幕的亮度0--255
     */
    public int getScreenBrightness() {
        int screenBrightness = 255;
        try {
            screenBrightness = Settings.System.getInt(getContext().getContentResolver(),
                    Settings.System.SCREEN_BRIGHTNESS);
        } catch (Exception localException) {

        }
        return screenBrightness;
    }

    /**
     * 设置当前屏幕亮度值 0--255
     */
    private void saveScreenBrightness(int paramInt) {
        try {
            Settings.System.putInt(getContext().getContentResolver(),
                    Settings.System.SCREEN_BRIGHTNESS, paramInt);
        } catch (Exception localException) {
            localException.printStackTrace();
        }
    }
    
    /**
     * 保存当前的屏幕亮度值，并使之生效
     */
    public void setScreenBrightness(Context context,int paramInt) {
        Window localWindow = ((Activity) context).getWindow();
        WindowManager.LayoutParams localLayoutParams = localWindow
                .getAttributes();
        float f = paramInt / 255.0F;
        localLayoutParams.screenBrightness = f;
        localWindow.setAttributes(localLayoutParams);
    }
   
}
