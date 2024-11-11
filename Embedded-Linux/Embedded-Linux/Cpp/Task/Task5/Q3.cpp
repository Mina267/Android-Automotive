class Solution {
public:
    std::string addStrings(std::string num1, std::string num2) {
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;
        std::string result;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0)
            { 
                sum += num1[i--] - '0';
            }
            if (j >= 0){
                sum += num2[j--] - '0';  
            } 
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};
