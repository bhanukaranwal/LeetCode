class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int rows = matrix.size(), cols = matrix[0].size();
        vector<int> heights(cols + 1, 0);
        int maxArea = 0;
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }
            stack<int> s;
            for (int j = 0; j <= cols; ++j) {
                while (!s.empty() && heights[j] < heights[s.top()]) {
                    int h = heights[s.top()];
                    s.pop();
                    int w = s.empty() ? j : j - s.top() - 1;
                    maxArea = max(maxArea, h * w);
                }
                s.push(j);
            }
        }
        return maxArea;
    }
};
