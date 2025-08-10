#include <vector>
#include <algorithm>
#include <numeric>

class UnionFind {
public:
    std::vector<int> parent;
    int count;

    UnionFind(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        count = n;
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
            count--;
            return true;
        }
        return false;
    }
};

class Solution {
public:
    std::vector<std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, std::vector<std::vector<int>>& edges) {
        // Store original indices along with edges
        std::vector<std::vector<int>> sortedEdges;
        for (int i = 0; i < edges.size(); ++i) {
            sortedEdges.push_back({edges[i][0], edges[i][1], edges[i][2], i}); // u, v, weight, original_index
        }

        // Sort edges by weight
        std::sort(sortedEdges.begin(), sortedEdges.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[2] < b[2];
        });

        // Step 1: Calculate the original MST weight
        int originalMSTWeight = getMSTWeight(n, sortedEdges, -1, -1);

        std::vector<int> criticalEdges;
        std::vector<int> pseudoCriticalEdges;

        // Step 2 & 3: Iterate through each edge to determine its type
        for (int i = 0; i < sortedEdges.size(); ++i) {
            int currentEdgeIndex = sortedEdges[i][3];

            // Check if critical (excluding current edge)
            int weightWithoutCurrent = getMSTWeight(n, sortedEdges, currentEdgeIndex, -1);
            if (weightWithoutCurrent > originalMSTWeight || weightWithoutCurrent == -1) {
                criticalEdges.push_back(currentEdgeIndex);
                continue; // It's critical, no need to check for pseudo-critical
            }

            // Check if pseudo-critical (forcing current edge)
            int weightWithCurrent = getMSTWeight(n, sortedEdges, -1, currentEdgeIndex);
            if (weightWithCurrent == originalMSTWeight) {
                pseudoCriticalEdges.push_back(currentEdgeIndex);
            }
        }

        return {criticalEdges, pseudoCriticalEdges};
    }

private:
    int getMSTWeight(int n, const std::vector<std::vector<int>>& sortedEdges, int excludeEdgeIndex, int includeEdgeIndex) {
        UnionFind uf(n);
        int currentMSTWeight = 0;
        int edgesUsed = 0;

        // If an edge must be included, add it first
        if (includeEdgeIndex != -1) {
            for (const auto& edge : sortedEdges) {
                if (edge[3] == includeEdgeIndex) {
                    uf.unite(edge[0], edge[1]);
                    currentMSTWeight += edge[2];
                    edgesUsed++;
                    break;
                }
            }
        }

        for (const auto& edge : sortedEdges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            int originalIndex = edge[3];

            if (originalIndex == excludeEdgeIndex) {
                continue; // Skip this edge if it's excluded
            }
            if (originalIndex == includeEdgeIndex) {
                continue; // Already included this edge
            }

            if (uf.unite(u, v)) {
                currentMSTWeight += weight;
                edgesUsed++;
            }
        }

        // Check if all vertices are connected (MST formed)
        if (edgesUsed == n - 1) {
            return currentMSTWeight;
        } else {
            return -1; // Graph is disconnected or MST not formed
        }
    }
};
