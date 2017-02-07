public class X
{
	static
	{
		System.loadLibrary("X");
	}

	private native void sayHello();

	public static void main(String[] args)
	{
		new X().sayHello();
	}
}
