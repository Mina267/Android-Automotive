#include <iostream>
#include <string>
#include <vector>



std::string HaystackReplace(std::string haystack, const std::string& needle, const std::string& replacement) {
    size_t p = haystack.find(needle);
    
    while (p != std::string::npos) 
    {
        haystack.replace(p, needle.length(), replacement);
        p = haystack.find(needle, p + replacement.length());
    }
    return std::move(haystack);
}







void Print(std::vector<std::vector<int>>& matrix)
{
    for (auto& arr : matrix)
    {
        for (auto& Val : arr)
        {
            std::cout << Val << " ";
        }
        std::cout << std::endl;

    }
}




std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>>& matrix)
{

    int cols = matrix[0].size();
    int j;
    std::vector<std::vector<int>> result(cols);

    for (const auto& row : matrix)
    {
        j = 0;
        for (const auto& val : row)
        {
            result[j].push_back(val);

            j++;
        }
    }
    std::cout << std::endl;

    Print(result);
    return result;
}





int main()
{
    
    std::string s = "The cycle of life is a cycle of cycles";
    std::string S_Replace = "cycle";
    std::string S_Replacement = "circle";

    auto p = s.find(S_Replace);
    while (p != std::string::npos)
    {
        s.replace(p, 5, S_Replacement);
        p = s.find(S_Replace);
    }

    std::cout << s << std::endl;

    p = s.find(S_Replacement);
    s.insert(p, "great ");

    std::cout << s << std::endl;

    auto p2 = s.find(S_Replacement, p + std::string("great ").size() + S_Replacement.size());
    s.insert(p2, "never-ending ");

    std::cout << s << std::endl;
    /******************************************************************/
    
    std::string haystack = "The cycle of life is a cycle of cycles";
    std::string needle = "cycle";
    std::string replacement = "circle";

    std::string result = HaystackReplace(haystack, needle, replacement);
    std::cout << "Result: " << result << std::endl;
    /*****************************************************************/

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    Print(matrix);
    Transpose(matrix);

    return 0;
}