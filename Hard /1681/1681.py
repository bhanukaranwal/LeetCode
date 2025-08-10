from collections import Counter

class Solution(object):
    def minimumIncompatibility(self, nums, k):
        n = len(nums)
        group_size = n // k

        # Early check: if any number appears more than k times, impossible
        if any(v > k for v in Counter(nums).values()):
            return -1

        # Precompute all valid groups (bitmask) and their incompatibility
        # Only consider groups of size group_size with unique elements
        from itertools import combinations

        valid = {}
        for comb in combinations(range(n), group_size):
            vals = [nums[i] for i in comb]
            if len(set(vals)) < group_size:
                continue
            mask = 0
            for i in comb:
                mask |= 1 << i
            valid[mask] = max(vals) - min(vals)

        # DP: dp[mask] = min sum of incompatibilities to cover 'mask'
        dp = [float('inf')] * (1 << n)
        dp[0] = 0

        for mask in range(1 << n):
            if bin(mask).count('1') % group_size != 0:
                continue
            # Try adding a valid group to mask
            for group_mask, incompat in valid.items():
                if (mask & group_mask) == 0:
                    new_mask = mask | group_mask
                    dp[new_mask] = min(dp[new_mask], dp[mask] + incompat)

        res = dp[(1 << n) - 1]
        return res if res < float('inf') else -1
