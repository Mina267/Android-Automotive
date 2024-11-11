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
				
				Integer spaces = (n * 2) + 1;
				Integer pos;
				Integer start = 0; 
				
				String s;
				
				s = '*' + 
				String.format("%" + spaces + "s", "") + '*';
				
				System.out.println(s);
				
				
				
				for (int i = 0; i < n; i++)
				{
					/* Spaces between two shapes */
					spaces -= 2;
					
					pos = s.indexOf('*', start);
					start = pos + 1;
					int last = s.lastIndexOf('*');
		
					s = s.substring(0, start) + '*' + 
					String.format("%" + spaces + "s", "")
					+  s.substring(start + spaces + 2, last + 1) + ' ' + '*';
					
					System.out.println(s);
	
				}
			}
			else
			{
				System.out.println("Enter number greater than zero!");
	
			}
		}
		
		
		
		
	}
}