package com.ancientlore.jscore.example;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.ancientlore.jscore.JSContext;
import com.ancientlore.jscore.JSFunction;
import com.ancientlore.jscore.JSValue;

public class MainActivity extends AppCompatActivity
{

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		JSContext context = new JSContext();

		JSFunction factorial = new JSFunction(context,"factorial") {
			public Integer factorial(Integer x) {
				int factorial = 1;
				for (; x > 1; x--) {
					factorial *= x;
				}
				return factorial;
			}
		};

		context.property("factorial", factorial);
		context.evaluateScript("var f = factorial(10);");
		JSValue f = context.property("f");

		TextView textView = findViewById(R.id.textView);
		textView.setText(f.toNumber() + "");
	}
}
