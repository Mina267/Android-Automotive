class Solution {
public:
	int addDigits(int num) {
	int newNum = 0;
	int result = num;
	while(result / 10 != 0)
	{
		newNum +=(num % 10);
		num /= 10;

		if (num == 0)
		{
			num = newNum;
			result = num;
			newNum = 0;
		}

	}

	return num;

};