class Parent
{
	private int no1;
	private int no2;
	
	public Parent()
	{
		no1 = 0;
	    no2 = 0;
	}
	
	public Parent(int n1)
	{
		no1 = n1;
	    no2 = n1;
	}
	
	public Parent(int n1, int n2)
	{
		no1 = n1;
	    no2 = n2;
	}
	
	public void setNo1(int n1)
	{
		no1 = n1;
	}
	
	public void setNo2(int n2)
	{
		no2 = n2;
	}
	
	public int getNo1()
	{
		return no1;
	}
	
	public int getNo2()
	{
		return no2;
	}
	
	public int sum()
	{
		return no1 + no2;
	}
	
}




class Child extends Parent
{
	private int no3;	
	public Child()
	{
		this(0, 0, 0);
	}
	
	public Child(int n1, int n3)
	{
		this(n1, n1, n3);
	}
	
	public Child(int n1, int n2, int n3)
	{
		super(n1, n2);
		no3 = n3;
	}
	
	public void setNo3(int n3)
	{
		no3 = n3;
	}
	
	public int getNo3()
	{
		return no3;
	}
	
	
	public int sum()
	{
		return no3 + super.sum();
	}
	
}


class MainClass
{
	public static void main(String[] args)
	{
		Child c1 = new Child(1, 2, 3);
		System.out.println("n1 = " + c1.getNo1());
		System.out.println("n2 = " + c1.getNo2());
		System.out.println("n3 = " + c1.getNo3());
		System.out.println("Sum = " + c1.sum());
		
		
		System.out.println("\n============================");

		Child c2 = new Child(1, 2);
		System.out.println("n1 = " + c2.getNo1());
		System.out.println("n2 = " + c2.getNo2());
		System.out.println("n3 = " + c2.getNo3());
		System.out.println("Sum = " + c2.sum());
		
		System.out.println("\n============================");
		
		Child c3 = new Child();
		System.out.println("n1 = " + c3.getNo1());
		System.out.println("n2 = " + c3.getNo2());
		System.out.println("n3 = " + c3.getNo3());
		System.out.println("Sum = " + c3.sum());
		
		System.out.println("\n============================");
		c3.setNo1(10);
		c3.setNo2(20);
		c3.setNo3(30);
		System.out.println("After setting new values:");
		System.out.println("n1 = " + c3.getNo1());
		System.out.println("n2 = " + c3.getNo2());
		System.out.println("n3 = " + c3.getNo3());
		System.out.println("Sum = " + c3.sum());
		

	}
}