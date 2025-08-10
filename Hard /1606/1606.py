from sortedcontainers import SortedList
import heapq

class Solution(object):
    def busiestServers(self, k, arrival, load):
        n = len(arrival)
        # Available servers (sorted for fast next-available lookup)
        available = SortedList(range(k))
        # Busy servers: (finish_time, server_id)
        busy = []
        # Count handled requests
        count = [0] * k

        for i, (start, duration) in enumerate(zip(arrival, load)):
            # Free up servers that have finished by now
            while busy and busy[0][0] <= start:
                _, server_id = heapq.heappop(busy)
                available.add(server_id)
            if not available:
                continue  # Drop the request
            # Find the server >= i % k (wrap around if needed)
            idx = available.bisect_left(i % k)
            if idx == len(available):
                idx = 0
            server = available[idx]
            available.remove(server)
            heapq.heappush(busy, (start + duration, server))
            count[server] += 1

        max_count = max(count)
        return [i for i, c in enumerate(count) if c == max_count]
