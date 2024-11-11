abstract class Shape
{
	private int dim1;
	
	public Shape()
	{
		dim1 = 0;		
	}
	
	public Shape(int n1)
	{
		dim1 = n1;
	}
	
	abstract double calcArea();
	
	public void setDim1(int n1)
	{
        dim1 = n1;
    }

	public int getDim1()
	{
		return dim1;
	}
	
}




class Triangle extends Shape
{
	private int dim2;
	
	public Triangle()
	{
		this(0, 0);
	}
	
	public Triangle(int n1, int n2)
	{
		super(n1);
        dim2 = n2;
	}
	
	public double calcArea()
	{
		return 0.5 * super.getDim1() * dim2;
	}
	
	public void setDim2(int n2)
	{
        dim2 = n2;
    }

	public int getDim2()
	{
		return dim2;
	}
	
}

class Circle extends Shape
{
	
	public Circle()
	{
		this(0);
	}
	
	public Circle(int n1)
	{
		super(n1);
	}
	
	public double calcArea()
	{
		return 3.14 * super.getDim1() * super.getDim1();
	}
	
	
	
}


class Rectangle extends Shape
{
	private int dim2;
	
	public Rectangle()
	{
		this(0, 0);
	}
	
	public Rectangle(int n1, int n2)
	{
		super(n1);
        dim2 = n2;
	}
	
	public double calcArea()
	{
		return super.getDim1() * dim2;
	}
	
	public void setDim2(int n2)
	{
        dim2 = n2;
    }

	public int getDim2()
	{
		return dim2;
	}
	
}




class MainClass
{

	static double calcSum(Shape s1, Shape s2, Shape s3)
	{
		return s1.calcArea() + s2.calcArea() + s3.calcArea();
	}

	public static void main(String[] args)
	{
		
		Triangle t = new Triangle(5, 5);
		Circle   c = new Circle(5);
		Rectangle r = new Rectangle(5, 5);
		
		System.out.println("Area1 = " + calcSum(t, c, r));
		
		System.out.println("Area1 = " + calcSum(r, c, t));
		
		System.out.println("Area1 = " + calcSum(t, t, t));
		
		System.out.println("Area1 = " + calcSum(r, r, r));
		
		System.out.println("Area1 = " + calcSum(c, c, c));

	}
}