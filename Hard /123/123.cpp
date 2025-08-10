#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        // We track the max profit at each of the 4 transaction stages.
        int buy1 = INT_MIN;    // Max profit after the first buy
        int sell1 = 0;         // Max profit after the first sell
        int buy2 = INT_MIN;    // Max profit after the second buy
        int sell2 = 0;         // Max profit after the second sell

        // Iterate through the prices one day at a time.
        for (int price : prices) {
            // The max profit after a second sell is either the previous max
            // or the profit from selling today (which requires a previous second buy).
            sell2 = std::max(sell2, buy2 + price);
            
            // The max profit after a second buy is either the previous max
            // or the profit from buying today (which requires a previous first sell).
            buy2 = std::max(buy2, sell1 - price);
            
            // The max profit after a first sell is either the previous max
            // or the profit from selling today (which requires a previous first buy).
            sell1 = std::max(sell1, buy1 + price);
            
            // The max profit after a first buy is either the previous max
            // or the profit from buying today (costing the current price).
            buy1 = std::max(buy1, -price);
        }

        // The final answer is the maximum profit after up to two sells.
        return sell2;
    }
};
