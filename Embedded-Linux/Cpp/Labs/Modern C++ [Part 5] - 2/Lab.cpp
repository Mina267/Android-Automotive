#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


class Battleship
{
private:
	std::vector<std::vector<bool>> board;
	int guesses;
	int maxGuesses;
	int locationX;
	int locationY;
public:
	Battleship(int maxGuesses) : guesses(0), maxGuesses(maxGuesses)
	{
		board = std::vector<std::vector<bool>>(5, std::vector<bool>(5, false));

		std::srand(std::time(0));
		locationX = std::rand() % 5;
		locationY = std::rand() % 5;
		board[locationX][locationY] = true;
	}

	bool guess(int x, int y)
	{
		bool status = false;
		++guesses;
		if (board[x][y])
		{
			status = true;
		}
		else
		{
			std::cout << "You miss the spot!... :(\n";
			if (x == locationX)
			{
				std::cout << "You are on the right X-axis as the Battleship!..\n";
			}
			else if (y == locationY)
			{
				std::cout << "You are on the right Y-axis as the Battleship!..\n";
			}
		}
		return status;
	}

	bool gameOver() const
	{
		return (maxGuesses == guesses);
	}

	int getGuesses() const
	{
		return guesses;
	}

	~Battleship()
	{
	}



};






int main()
{
	const int maxGuesses = 5;
	Battleship game(maxGuesses);
	int x, y;
	bool WonFlag = false;

	std::cout << "Welcome to Battleship!\n";
	std::cout << "You have " << maxGuesses << " guesses to find the battleship hidden in a 5x5 grid.\n";

	while (!game.gameOver())
	{
		std::cout << "Enter your guess (row and column): ";
		std::cin >> x >> y;


		if ((x > 0 && x <= 5) && (y > 0 && y <= 5))
		{
			if (game.guess(x - 1, y - 1))
			{
				std::cout << "You hit the battleship!\n";
				std::cout << "You won in " << game.getGuesses() << " guesses!\n";
				WonFlag = true;
				break;
			}
			else
			{
				std::cout << "You have " << (maxGuesses - game.getGuesses()) << " guesses left.\n";
			}
		}
		else
		{
			std::cout << "Invalid coordinates. Please enter values between 1 and 5.\n";
		}

	}

	if (WonFlag == false)
	{
		std::cout << "Game over! You've used all your guesses.\n";
	}

	return 0;
}
