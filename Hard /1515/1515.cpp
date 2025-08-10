class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        if (positions.size() == 1) return 0.0;
        double x = 0, y = 0;
        int n = positions.size();
        for (auto& p : positions) {
            x += p[0];
            y += p[1];
        }
        x /= n;
        y /= n;

        double eps = 1e-7;
        double change = 1e9;

        while (change > eps) {
            double numX = 0, numY = 0, denom = 0;
            bool atPoint = false;
            for (auto& p : positions) {
                double dx = x - p[0], dy = y - p[1];
                double dist = sqrt(dx * dx + dy * dy);
                if (dist < eps) {
                    atPoint = true;
                    break;
                }
                numX += p[0] / dist;
                numY += p[1] / dist;
                denom += 1.0 / dist;
            }
            if (atPoint) break;
            double newX = numX / denom;
            double newY = numY / denom;
            change = sqrt((x - newX) * (x - newX) + (y - newY) * (y - newY));
            x = newX;
            y = newY;
        }

        double result = 0;
        for (auto& p : positions)
            result += sqrt((x - p[0]) * (x - p[0]) + (y - p[1]) * (y - p[1]));
        return result; // Now 'result' is declared and assigned
    }
};
