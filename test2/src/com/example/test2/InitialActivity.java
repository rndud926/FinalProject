package com.example.test2;



public class InitialActivity extends Activity
{
	EditText edtIP;
	EditText edtPort;
	
	Button btnConfirm;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.initial);
		
		SharedPreferences pref = getSharedPreferences("UH", 0);
		String strIP = pref.getString("IP", "203.230.104.123");
		
		edtIP = (EditText) findViewById(R.id.edtIP);
		edtIP.setText(strIP);
		
		btnConfirm = (Button) findViewById(R.id.btnConfirm);
		btnConfirm.setOnClickListener(new Button.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				SharedPreferences pref = getSharedPreferences("UH", 0);
				SharedPreferences.Editor edit = pref.edit();
				edit.putString("IP", edtIP.getText().toString());
				edit.commit();
				
				Intent intent = new Intent(InitialActivity.this, MainActivity.class);
				intent.putExtra("IP", edtIP.getText().toString());
				startActivity(intent);
				finish();
			}
		});
	}
}
