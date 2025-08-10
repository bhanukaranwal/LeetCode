#include <string>
#include <stack>
#include <cctype>

class Solution {
public:
    int calculate(std::string s) {
        std::stack<int> st; // Stack to store results and signs from outer scopes
        long long current_result = 0;
        int sign = 1; // 1 for '+', -1 for '-'
        
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];

            if (std::isdigit(c)) {
                // Parse the entire number which could have multiple digits
                long long num = 0;
                while (i < s.length() && std::isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                // Decrement i because the outer for-loop will increment it
                i--; 
                
                current_result += sign * num;
            } else if (c == '+') {
                sign = 1;
            } else if (c == '-') {
                sign = -1;
            } else if (c == '(') {
                // Start of a new sub-expression, save the current state
                st.push(current_result);
                st.push(sign);
                
                // Reset for the inner expression
                current_result = 0;
                sign = 1;
            } else if (c == ')') {
                // End of a sub-expression, merge with the saved state
                
                // Pop the sign that preceded the parentheses
                int prev_sign = st.top();
                st.pop();
                
                // Pop the result from the outer scope
                long long prev_result = st.top();
                st.pop();
                
                // Calculate the combined result
                current_result = prev_result + (prev_sign * current_result);
            }
            // Spaces are ignored automatically
        }
        
        return (int)current_result;
    }
};
