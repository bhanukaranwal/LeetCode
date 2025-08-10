class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return trim(helper(num));
    }
private:
    vector<string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                               "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> thousands = {"", " Thousand", " Million", " Billion"};
    vector<long long> units = {1LL, 1000LL, 1000000LL, 1000000000LL};

    string helper(long long num) {
        if (num == 0) return "";
        if (num < 20) return " " + below_20[num];
        if (num < 100) return " " + tens[num/10] + helper(num%10);
        if (num < 1000) return helper(num/100) + " Hundred" + helper(num%100);
        for (int i = 3; i >= 1; --i) {
            if (num >= units[i]) {
                return helper(num/units[i]) + thousands[i] + helper(num%units[i]);
            }
        }
        return "";
    }
    string trim(string s) {
        // Remove leading space if any
        if (!s.empty() && s[0] == ' ') return s.substr(1);
        return s;
    }
};
