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
			String[] s = ip.split("\\.");
	
			for (String i : s)
			{
				System.out.println(i);
			}
		}

        
			
	}
}

