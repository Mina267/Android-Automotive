class Calc
{
	public static void main(String[] args)
	{
		
		
		if (args.length != 3) {
            System.out.println("Enter Only three argument!");
        }
		else
		{
			Double n1 = Double.parseDouble(args[0]);
			Double n2 = Double.parseDouble(args[2]);
			Double r = 0D;
			Boolean f = true;

			switch (args[1]) {
				case "+":
					r = n1 + n2;
					break;
				case "-":
					r = n1 - n2;
					break;
				case "x":
					r = n1 * n2;
					break;
				case "/":
					if (n2 != 0) {
						r = n1 / n2;
					} 
					else {
						System.out.println("Division by zero!");
						f = false;
					}
					break;
				default:
					System.out.println("Invalid operator. Please use (+, -, x, /) only.");
					f = false;
					break;
			}
			
			if (f)
			{
				System.out.println("The r = " + r);
				
			}
		}
	}
}