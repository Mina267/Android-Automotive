class Shape
{
	public static void main(String[] args)
	{
		
		
		if (args.length != 1) {
            System.out.println("Enter Only one argument!");
        }
		else
		{
			Integer n = Integer.parseInt(args[0]);
			if (n != 0)
			{
				Integer spaces = (n * 2) - 1;
				
				String s1 = new String("*");
				String s2 = new String("*");

				for (int i = 0; i < n; i++)
				{
					System.out.println(s1 + String.format("%" + spaces + "s", " ") + s2);
					
					/* Spaces between two shapes */
					spaces -= 2;
					/* Append to shap1 */
					s1 += '*';
					/* Append to shap2 */
					s2 = s2 + ' ' + '*';					
				}
			}
			else
			{
				System.out.println("Enter number greater than zero!");
	
			}
		}
		
		
		
		
	}
}