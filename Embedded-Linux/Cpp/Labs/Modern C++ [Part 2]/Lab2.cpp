#include <iostream>

enum class ErrorCode
{
    BAD_REQUEST,
    NOT_FOUND,
    SERVER_ERROR,
    GATEWAY_TIMEOUT
};

void Error(ErrorCode Error)
{
    switch (Error)
    {
    case ErrorCode::BAD_REQUEST:
        std::cout << "400 Bad Request\n";
        break;
    case ErrorCode::NOT_FOUND:
        std::cout << "404 Not Found\n";
        break;
    case ErrorCode::SERVER_ERROR:
        std::cout << "500 Server Error\n";
        break;
    case ErrorCode::GATEWAY_TIMEOUT:
        std::cout << "504 Gatway timout\n";
        break;
    default:
        std::cout << "Undefined Error!\n";
        break;
    }

}

int main()
{
    Error(ErrorCode::GATEWAY_TIMEOUT);
}
