class Solution(object):
    def maximumRequests(self, n, requests):
        max_ans = 0
        m = len(requests)
        for mask in range(1 << m):
            net = [0] * n
            count = 0
            for i in range(m):
                if (mask >> i) & 1:
                    from_b, to_b = requests[i]
                    net[from_b] -= 1
                    net[to_b] += 1
                    count += 1
            if all(x == 0 for x in net):
                max_ans = max(max_ans, count)
        return max_ans
