#include <vector>
#include <set>
#include <algorithm> // For std::min, std::max
#include <climits>   // For INT_MAX, INT_MIN

class Solution {
public:
    // Renamed the function to isRectangleCover to match the error message's expectation
    bool isRectangleCover(std::vector<std::vector<int>>& rectangles) {
        if (rectangles.empty()) {
            // According to LeetCode's typical behavior for such problems,
            // an empty set of rectangles should probably not form a perfect rectangle.
            // If the problem intended otherwise, the constraints or examples would clarify.
            return false;
        }

        long long totalArea = 0;
        
        // Initialize min/max coordinates for the overall bounding box
        int minX = INT_MAX, minY = INT_MAX;
        int maxX = INT_MIN, maxY = INT_MIN;

        // A set to store corner points.
        // The idea is that if a point is a true corner of the final perfect rectangle,
        // it should appear an odd number of times (specifically, once).
        // All other internal points that are properly covered should appear an even number of times.
        std::set<std::pair<int, int>> corners;

        for (const auto& rect : rectangles) {
            int x1 = rect[0];
            int y1 = rect[1];
            int x2 = rect[2];
            int y2 = rect[3];

            // Update bounding box coordinates
            minX = std::min(minX, x1);
            minY = std::min(minY, y1);
            maxX = std::max(maxX, x2);
            maxY = std::max(maxY, y2);

            // Add individual rectangle area to total area. Use long long to prevent overflow.
            totalArea += (long long)(x2 - x1) * (y2 - y1);

            // Process the four corner points of the current rectangle.
            // We use the set to track point counts:
            // If a point is already in the set, it means it's appeared an odd number of times before.
            // Adding it again makes it an even occurrence, so remove it.
            // If a point is not in the set, it means it's appeared an even number of times before.
            // Adding it now makes it an odd occurrence, so insert it.
            auto toggle_point = [&](int px, int py) {
                std::pair<int, int> p = {px, py};
                if (corners.count(p)) { 
                    corners.erase(p);
                } else { 
                    corners.insert(p);
                }
            };

            toggle_point(x1, y1);
            toggle_point(x1, y2);
            toggle_point(x2, y1);
            toggle_point(x2, y2);
        }

        // --- Validation ---

        // Condition 1: Check if the 'corners' set contains exactly the four corners of the overall bounding rectangle.
        // For a perfect rectangle, only the four outermost corners should have an odd frequency (i.e., appear once).
        // All other internal points should have an even frequency (i.e., be removed from the set).
        if (corners.size() != 4) {
            return false;
        }

        // And these 4 points must be precisely the bottom-left, top-left, bottom-right, and top-right
        // corners of the overall bounding box determined by minX, minY, maxX, maxY.
        if (!corners.count({minX, minY}) ||
            !corners.count({minX, maxY}) ||
            !corners.count({maxX, minY}) ||
            !corners.count({maxX, maxY})) {
            return false;
        }

        // Condition 2: Check if the sum of individual areas equals the area of the bounding rectangle.
        // This ensures no overlaps (totalArea would be greater) and no gaps (totalArea would be smaller).
        long long boundingBoxArea = (long long)(maxX - minX) * (maxY - minY);
        if (totalArea != boundingBoxArea) {
            return false;
        }

        return true; // All conditions met, it's a perfect rectangle
    }
};
