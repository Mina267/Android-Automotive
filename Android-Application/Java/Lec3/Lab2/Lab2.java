class IPCutter
{
	public static void main(String[] args)
	{
		
		if (args.length != 1) {
            System.out.println("Error only one arg");
        }
		else
		{
			String ip = args[0];
			Integer start = 0;
			
			/*
			*  public String substring(int beginIndex,
			*              int endIndex)
			*  Parameters:
			*	ch - a character (Unicode code point).
			*	fromIndex - the index to start the search from. 
			*	Returns:
			*	the index of the first occurrence of the character in the character sequence represented by this object that is greater than or equal to fromIndex, or -1 if the character does not occur.
			*/
			Integer dotPos = ip.indexOf('.', start);
			
			while (dotPos != -1)
			{
				/* 	
				* Parameters: beginIndex - the beginning index, inclusive.
				*				endIndex - the ending index, exclusive. 
				*	Returns: the specified substring.   
				*/
				String sub = ip.substring(start, dotPos);
				
				start = dotPos + 1;
				
				System.out.println(sub);
	
				dotPos = ip.indexOf('.', start);
				
				
			}
			
			
			/* 
			* public String substring(int beginIndex)
			* Returns a new string that is a substring of this string. The substring begins with the character at the specified index and extends to the end of this string. 
			* Parameters:
			* beginIndex - the beginning index, inclusive. 
			* Returns:
			* the specified substring. 
			*/
			
			//System.out.println("lAST = " + start);
			
			/* 
			* Returns:
			* the length of the sequence of characters represented by this object. 
			*/
			if (start < ip.length()) 
			{
				String sub = ip.substring(start);
				System.out.println(sub);
			}
		}

        
		
	}
}

