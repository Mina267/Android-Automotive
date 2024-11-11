#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

class Vertex
{
    int x;
    int y;
public:
    /* Default constructor */
	Vertex():x(0), y(0){}

    /* Member function to set(x, y) with random numbers */
    void setRandomValues()
    {
        x = std::rand() % 201 - 100;
        y = std::rand() % 201 - 100;
    }

    // Getter for x
    int getX() const {
        return x;
    }

    // Getter for y
    int getY() const {
        return y;
    }

    /* Convert c and y into output string */
    std::string toString()
    {
        return "Vertex(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }

	~Vertex()
	{
	}

private:

};


int main() {

    std::srand(std::time(0));

    // Generate 5 random vertices
    Vertex vertices[5];
    for (int i = 0; i < 5; ++i) {
        vertices[i].setRandomValues();
    }

    // Output 
    for (int i = 0; i < 5; ++i) {
        std::cout << vertices[i].toString() << std::endl;
    }

    return 0;
}