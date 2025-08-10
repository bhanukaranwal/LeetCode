class Solution(object):
    def minimumBoxes(self, n):
        s, k = 0, 1
        # Build as many full layers as possible
        while s + k * (k + 1) // 2 <= n:
            s += k * (k + 1) // 2
            k += 1
        k -= 1
        ans = k * (k + 1) // 2  # number of boxes on the floor in full pyramid
        # Add more boxes one by one if needed
        more = 1
        while s < n:
            ans += 1
            s += more
            more += 1
        return ans
