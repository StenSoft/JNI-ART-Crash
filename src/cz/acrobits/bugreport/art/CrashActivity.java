package cz.acrobits.bugreport.art;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.Method;

import android.app.Activity;
import android.os.Bundle;


public class CrashActivity
		extends Activity
{
	@Target(ElementType.TYPE)
	@Retention(RetentionPolicy.RUNTIME)
	public static @interface Annotation
	{
		int value();
	}

	@Annotation(0)
	public static class Annotated
	{}

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		// First, try reflection from Java
		try
		{
			Annotation annotation = Annotated.class.getAnnotation(Annotation.class);
			Method value = Annotation.class.getMethod("value");
			value.invoke(annotation);
		}
		catch (Exception e)
		{
			throw new RuntimeException(e);
		}

		// Now, try the same from JNI
		crash();
	}

	public native void crash();

	static
	{
		System.loadLibrary("crash");
	}
}
