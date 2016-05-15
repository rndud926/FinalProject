package com.example.test2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	//NDK
	static{
		System.loadLibrary("test2");
	}
	
	public static native int Init(String ip);
	public static native void CreatedGlView();
	public static native void UpdateGlView();
	public static native void ChangedGlView(int width, int height);
	
	private Button mybutton;
	private RelativeLayout layout_joystick;
	private ImageView image_joystick, image_border;
	private TextView textView1, textView2, textView3, textView4, textView5;
	private JoyStickClass js;
	
	private String strip;
	public UHSurfaceView mUHSurfaceView;
	
	  @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fragment_main);
        
        Log.v("LOG", "CREATE");
        Intent intent = getIntent();
		strip = intent.getStringExtra("IP");
		Log.v("IP", strip);
        int connection = MainActivity.Init(strip);
        if(connection == -1)
        {
        	Toast msg = Toast.makeText(this	, "서버접속실패.", Toast.LENGTH_SHORT);
        	msg.show();
        	finish();
        }
        
        mUHSurfaceView = (UHSurfaceView) findViewById(R.id.uhsurfaceview); //surfaceview creation
      	textView1 = (TextView)findViewById(R.id.textView1);
        Log.v("LOG", "TEXTVIEW");
        
        textView2 = (TextView)findViewById(R.id.textView2);
        textView3 = (TextView)findViewById(R.id.textView3);
        textView4 = (TextView)findViewById(R.id.textView4);
        textView5 = (TextView)findViewById(R.id.textView5);
        
        layout_joystick = (RelativeLayout)findViewById(R.id.layout_joystick);

        //Log.v("LOG", "END_ONCREATE");
	    
        js = new JoyStickClass(getApplicationContext(), layout_joystick, R.drawable.image_button);
        //Log.v("LOG", "END_ONCREATE");
	    
        js.setStickSize(100, 100);
	    js.setLayoutSize(300, 300);
	    js.setLayoutAlpha(100);
	    js.setStickAlpha(100);	
	    js.setOffset(90);
	    js.setMinimumDistance(5);
        layout_joystick.setOnTouchListener(new OnTouchListener() 
		{
			public boolean onTouch(View arg0, MotionEvent arg1) {
				js.drawStick(arg1);
				if(arg1.getAction() == MotionEvent.ACTION_DOWN
						|| arg1.getAction() == MotionEvent.ACTION_MOVE) {
					textView1.setText("X : " + String.valueOf(js.getX()));
					textView2.setText("Y : " + String.valueOf(js.getY()));
					textView3.setText("Angle : " + String.valueOf(js.getAngle()));
					textView4.setText("Distance : " + String.valueOf(js.getDistance()));
					
					int direction = js.get8Direction();
					if(direction == JoyStickClass.STICK_UP) {
						textView5.setText("Direction : Up");
					} else if(direction == JoyStickClass.STICK_UPRIGHT) {
						textView5.setText("Direction : Up Right");
					} else if(direction == JoyStickClass.STICK_RIGHT) {
						textView5.setText("Direction : Right");
					} else if(direction == JoyStickClass.STICK_DOWNRIGHT) {
						textView5.setText("Direction : Down Right");
					} else if(direction == JoyStickClass.STICK_DOWN) {
						textView5.setText("Direction : Down");
					} else if(direction == JoyStickClass.STICK_DOWNLEFT) {
						textView5.setText("Direction : Down Left");
					} else if(direction == JoyStickClass.STICK_LEFT) {
						textView5.setText("Direction : Left");
					} else if(direction == JoyStickClass.STICK_UPLEFT) {
						textView5.setText("Direction : Up Left");
					} else if(direction == JoyStickClass.STICK_NONE) {
						textView5.setText("Direction : Center");
					}
				} else if(arg1.getAction() == MotionEvent.ACTION_UP) {
					textView1.setText("X :");
					textView2.setText("Y :");
					textView3.setText("Angle :");
					textView4.setText("Distance :");
					textView5.setText("Directi"
							+ "on :");
				}
				return true;
			}
        });

        Log.v("LOG", "END_ONCREATE");
    }
}
