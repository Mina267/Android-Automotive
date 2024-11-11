class Complex
{
	private int real;
	private int img;
	
	
	public Complex()
	{
		real = 0;
		img = 0;
	}
	
	public Complex(int n1, int n2)
	{
		real = n1;
		img = n2;
	}

	public void setReal(int n1)
	{
        real = n1;
    }

	public int getReal()
	{
		return real;
	}
	
	public void setImg(int n1)
	{
        img = n1;
    }

	public int getImg()
	{
		return img;
	}
	
	public static Complex add(Complex c1, Complex c2)
	{
		Complex cr = new Complex();
		cr.setReal(c1.getReal() + c2.getReal());
		cr.setImg(c1.getImg() + c2.getImg());
		return cr;
	}
	
	
	public Complex add(Complex c1)
	{
		Complex cr = new Complex();
		cr.setReal(c1.getReal() + real);
		cr.setImg(c1.getImg() + img);
		return cr;
	}
	
	public static Complex subs(Complex c1, Complex c2)
	{
		Complex cr = new Complex();
		cr.setReal(c1.getReal() - c2.getReal());
		cr.setImg(c1.getImg() - c2.getImg());
		return cr;
	}
	
	public void print()
	{
		if (img > 0)
			System.out.println("R = " + real + "+" + img + "j");
		else
			System.out.println("R = " + real + img + "j");
	}
}







class MainClass
{

	
	public static void main(String[] args)
	{
		System.out.println("Create c1:");
		Complex c1 = new Complex(-5, -6);
		c1.print();
		
		System.out.println("Create c2:");
		Complex c2 = new Complex(10, 10);
		c2.print();
		
		
		System.out.println("ADD:");
		Complex c3 = Complex.add(c1, c2);
		c3.print();
		
		System.out.println("Subs:");
		c3 = Complex.subs(c1, c2);
		c3.print();
		
		System.out.println("ADD:");
		c3 = c1.add(c2);
		c3.print();
		
		
		
		
	}
}