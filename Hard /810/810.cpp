#include <vector>
#include <numeric>

class Solution {
public:
    bool xorGame(std::vector<int>& nums) {
        // Calculate the bitwise XOR of all numbers on the board.
        int xor_sum = 0;
        for (int num : nums) {
            xor_sum ^= num;
        }
        
        // According to the rules, Alice wins immediately if the starting
        // XOR sum is 0.
        if (xor_sum == 0) {
            return true;
        }
        
        // If the initial XOR sum is not 0, the game outcome depends
        // on the number of elements.
        // If there's an even number of elements, Alice can always make a
        // move that doesn't result in a XOR sum of 0. This forces the
        // game to continue, eventually leaving Bob in a losing position.
        // If there's an odd number of elements, Bob can mirror this
        // strategy, forcing Alice to lose.
        return nums.size() % 2 == 0;
    }
};
