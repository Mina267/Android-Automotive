#define SET_BIT(REG, BIT) (REG |= (1 << BIT))

int covert(std::string &Binary)
{
	int n = 0;
	int cnt = 0;
	int len = Binary.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (Binary[i] == '1')
		{
			SET_BIT(n, cnt);
		}
		cnt++;
	}
	return n;
}


std::string covert(unsigned int n)
{
	unsigned int bit = 1 << 31;
	std::string s;
	while (bit)
	{
		if ((n & bit) != 0)
		{
			s += "1";
		}
		else
		{
			s += "0";
		}
		bit = bit >> 1;
	}
	return s;
}

int main() {
	std::string s{ "00111111" };
	std::cout << covert(s) << std::endl;

	std::cout << covert(63) << std::endl;

    return 0;
}

