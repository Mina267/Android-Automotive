

int main()
{
    int n = 0;
    static int result = 0;
    std::cout << "Please Enter Number : ";
    std::cin >> n;

    while (true)
    {
        if (n != 0)
        {
            result += n;
        }
        else
        {
            break;
        }
        std::cout << "Please Enter another Number : ";
        std::cin >> n;
    }

    std::cout << "Result : " << result;

    return 0;
}
