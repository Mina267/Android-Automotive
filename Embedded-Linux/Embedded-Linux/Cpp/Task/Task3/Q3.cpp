class ParkingSystem {
int spaces[3];
public:
	ParkingSystem(int big, int medium, int small): spaces{big, medium, small} {	}



	bool addCar(int carType) {
	if (spaces[carType -1])
	{

		--spaces[carType - 1];
		return true;
	}

		return false;
	}
};