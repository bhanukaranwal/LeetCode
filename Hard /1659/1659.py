class Solution(object):
    def getMaxGridHappiness(self, m, n, introvertsCount, extrovertsCount):
        memo = {}

        def get(state, idx):
            return (state // (3 ** idx)) % 3

        def dp(pos, state, in_left, ex_left):
            key = (pos, state, in_left, ex_left)
            if key in memo:
                return memo[key]
            if pos == m * n or (in_left == 0 and ex_left == 0):
                return 0
            i, j = divmod(pos, n)
            res = dp(pos + 1, state * 3 % (3 ** n), in_left, ex_left)  # Leave empty

            # Neighboring cells (up and left)
            up = get(state, n - 1) if i > 0 else 0
            left = get(state, 0) if j > 0 else 0

            # Place introvert
            if in_left:
                happy = 120
                for nb in [up, left]:
                    if nb == 1: happy -= 60  # Both lose 30
                    elif nb == 2: happy -= 10  # Introvert -30, Extrovert +20
                res = max(res, happy + dp(
                    pos + 1, (state * 3 + 1) % (3 ** n), in_left - 1, ex_left))
            # Place extrovert
            if ex_left:
                happy = 40
                for nb in [up, left]:
                    if nb == 1: happy += -10  # Extrovert +20, Introvert -30
                    elif nb == 2: happy += 40  # Both gain 20
                res = max(res, happy + dp(
                    pos + 1, (state * 3 + 2) % (3 ** n), in_left, ex_left - 1))
            memo[key] = res
            return res

        return dp(0, 0, introvertsCount, extrovertsCount)
