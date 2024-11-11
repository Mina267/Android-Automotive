#include <iostream>
#include <string>

class Car
{
	std::string company;
	std::string model;
	int year;
public:
	
	Car(std::string company, std::string model, int year): company(company), model(model), year(year) {}

	void set_Company(const std::string company)
	{
		this->company = company;
	}

	const std::string get_Company(void) const
	{
		return company;
	}
	void set_Model(const std::string model)
	{
		this->model = model;
	}

	const std::string get_Model(void) const
	{
		return model;
	}

	void set_Year(const int year)
	{
		this->year = year;
	}

	const int get_Year() const
	{
		return year;
	}
};

int main() {
	/* Create a Car object intialize with parameterize constructor */
	Car myCar("Toyota", "Corolla", 2020);

	std::cout << "Company: " << myCar.get_Company() << std::endl;
	std::cout << "Model: " << myCar.get_Model() << std::endl;
	std::cout << "Year: " << myCar.get_Year() << std::endl;

	std::cout << "\n=====================\n" << std::endl;


	/* Modify values */
	myCar.set_Company("Honda");
	myCar.set_Model("Civic");
	myCar.set_Year(2022);

	// Output modified values
	std::cout << "Company: " << myCar.get_Company() << std::endl;
	std::cout << "Model: " << myCar.get_Model() << std::endl;
	std::cout << "Year: " << myCar.get_Year() << std::endl;

	return 0;
}