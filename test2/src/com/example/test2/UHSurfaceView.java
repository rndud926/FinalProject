package com.example.test2;


public class UHSurfaceView extends GLSurfaceView {
	
	public UHSurfaceView(Context context)
	{
		super(context);
		setEGLConfigChooser(false);
		setRenderer(new KRenderer());
	}
	
	public UHSurfaceView(Context context, AttributeSet attrs)
	{
		super(context, attrs);
		setEGLConfigChooser(false);
		setRenderer(new KRenderer());
	}

	class KRenderer implements Renderer
	{
		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config)
		{
			MainActivity.CreatedGlView();
		}
		
		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height)
		{
			MainActivity.ChangedGlView(width, height);
		}
		
		@Override
		public void onDrawFrame(GL10 gl)
		{
			MainActivity.UpdateGlView();
		}
	}
}
