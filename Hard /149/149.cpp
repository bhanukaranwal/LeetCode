#include <vector>
#include <map>
#include <numeric>   // Required for std::gcd in C++17
#include <algorithm> // Required for std::max

class Solution {
public:
    int maxPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();
        if (n <= 2) {
            return n;
        }

        int max_count = 0;

        // Iterate through each point, treating it as an anchor.
        for (int i = 0; i < n; ++i) {
            // Map to store slopes relative to the anchor point points[i].
            // Key: a pair {dy, dx} representing the reduced slope.
            // Value: the number of points with that slope.
            std::map<std::pair<int, int>, int> slope_map;
            
            // Iterate through the other points to calculate slopes.
            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                // Vertical line case
                if (dx == 0) {
                    slope_map[{1, 0}]++;
                } else { // All other lines
                    int common_divisor = std::gcd(dx, dy);
                    dx /= common_divisor;
                    dy /= common_divisor;
                    
                    // Normalize to ensure a consistent representation for each slope.
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                    slope_map[{dy, dx}]++;
                }
            }
            
            // Find the maximum number of points for the current anchor point.
            int current_max = 0;
            for (auto const& [slope, count] : slope_map) {
                current_max = std::max(current_max, count);
            }
            
            // Update the overall maximum. Add 1 for the anchor point itself.
            max_count = std::max(max_count, current_max + 1);
        }

        return max_count;
    }
};
