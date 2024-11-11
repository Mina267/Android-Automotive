
int annualGrowth(double population, double Targetpopulation, float growthRate)
{
	int Years = 0;
	while (population <= Targetpopulation)
	{
		population += (population * growthRate);
		Years++;
	}
	return Years;
}


int calculateYears(double initialPopulation, double targetPopulation, double growthRate)
{
	return std::ceil(std::log(targetPopulation / initialPopulation) / std::log(1 + growthRate));
}

int main() {

	std::cout << annualGrowth(162100, 1000000, 0.065) << std::endl;
	std::cout << calculateYears(162100, 1000000, 0.065) << std::endl;

	return 0;
}

