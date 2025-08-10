from collections import Counter

class Solution(object):
    def canDistribute(self, nums, quantity):
        counts = sorted(Counter(nums).values(), reverse=True)
        m = len(quantity)
        quantity.sort(reverse=True)
        memo = {}

        def backtrack(i, stocks):
            key = (i, tuple(sorted(stocks, reverse=True)))
            if key in memo:
                return memo[key]
            if i == m:
                return True
            for j in range(len(stocks)):
                if stocks[j] >= quantity[i]:
                    new_stocks = list(stocks)
                    new_stocks[j] -= quantity[i]
                    if backtrack(i+1, new_stocks):
                        memo[key] = True
                        return True
            memo[key] = False
            return False

        return backtrack(0, counts)
