#include <iostream>
#include <cstdlib>
#include <ctime>

// Define the Vertex structure
struct Vertex {
    int x;
    int y;
};

int main() {
    std::srand(std::time(0));

    // Generate 5 random vertices
    Vertex vertices[5];
    for (int i = 0; i < 5; ++i) {
        vertices[i].x = std::rand() % 201 - 100; 
        vertices[i].y = std::rand() % 201 - 100; 
    }

    // Output the vertices to the terminal
    for (int i = 0; i < 5; ++i) {
        std::cout << "Vertex " << i + 1 << ": (" << vertices[i].x << ", " << vertices[i].y << ")\n";
    }

    return 0;
}
