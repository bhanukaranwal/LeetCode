#include <vector>
#include <string>
#include <map>
#include <algorithm> // For std::reverse

class Solution {
public:
    // Adjacency list: map from origin airport to a map of destination airports and their counts
    std::map<std::string, std::map<std::string, int>> adj;
    std::vector<std::string> itinerary;

    void dfs(const std::string& current_airport) {
        // Iterate through the destinations from the current airport
        // The map automatically iterates in lexicographical order
        for (auto it = adj[current_airport].begin(); it != adj[current_airport].end(); ++it) {
            std::string next_airport = it->first;
            int& ticket_count = it->second; // Get a reference to the count

            if (ticket_count > 0) {
                // Use the ticket
                ticket_count--;
                dfs(next_airport);
            }
        }
        // After visiting all reachable airports from current_airport
        // and using all tickets from it, add current_airport to the itinerary.
        // This builds the itinerary in reverse order.
        itinerary.push_back(current_airport);
    }

    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) {
        // Build the adjacency list
        for (const auto& ticket : tickets) {
            adj[ticket[0]][ticket[1]]++;
        }

        // Start DFS from "JFK"
        dfs("JFK");

        // The itinerary is built in reverse order, so reverse it to get the correct path
        std::reverse(itinerary.begin(), itinerary.end());

        return itinerary;
    }
};
