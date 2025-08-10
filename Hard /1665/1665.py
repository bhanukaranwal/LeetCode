class Solution(object):
    def minimumEffort(self, tasks):
        # Sort tasks by (minimum - actual) descending
        tasks.sort(key=lambda x: x[1] - x[0], reverse=True)
        res = 0
        curr = 0
        for actual, minimum in tasks:
            # If current energy is less than minimum, increase initial energy
            if curr < minimum:
                res += minimum - curr
                curr = minimum
            curr -= actual
        return res
