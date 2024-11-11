import java.util.StringTokenizer;
class IPCutter
{
	public static void main(String[] args)
	{
		
		if (args.length != 1) {
            System.out.println("Error only one arg");
            return;
        }
		else
		{
			/*
			* public StringTokenizer(String str,
			*               String delim)
			* Constructs a string tokenizer for the specified string. The characters in the delim argument are the delimiters for separating tokens. Delimiter characters themselves will not be treated as tokens. 
			* Note that if delim is null, this constructor does not throw an exception. However, trying to invoke other methods on the resulting StringTokenizer may result in a NullPointerException. 
			* 
			* 
			* Parameters:
			* str - a string to be parsed.
			* delim - the delimiters. 
			*
			*/
			
			String ip = args[0];
			StringTokenizer st = new StringTokenizer(ip, ".");
			while (st.hasMoreTokens()) {
			System.out.println(st.nextToken());
			}
		}
		
	   
 
		
			
	}
}

