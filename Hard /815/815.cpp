class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        // Map stop -> list of routes containing that stop
        unordered_map<int, vector<int>> stopToRoutes;
        int n = routes.size();
        for (int i = 0; i < n; ++i) {
            for (int stop : routes[i]) {
                stopToRoutes[stop].push_back(i);
            }
        }

        // BFS initialization
        queue<int> q; // bus routes queue
        vector<bool> visitedRoutes(n, false);
        unordered_set<int> visitedStops;
        
        // Enqueue all routes passing through source
        for (int route : stopToRoutes[source]) {
            q.push(route);
            visitedRoutes[route] = true;
        }
        
        int busesTaken = 1;

        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int route = q.front(); q.pop();
                // Check if this route contains the target
                for (int stop : routes[route]) {
                    if (stop == target) return busesTaken;
                }
                // Explore neighboring routes via stops
                for (int stop : routes[route]) {
                    if (visitedStops.count(stop)) continue;
                    visitedStops.insert(stop);
                    for (int nextRoute : stopToRoutes[stop]) {
                        if (!visitedRoutes[nextRoute]) {
                            visitedRoutes[nextRoute] = true;
                            q.push(nextRoute);
                        }
                    }
                }
            }
            ++busesTaken;
        }

        return -1; // target not reachable
    }
};
