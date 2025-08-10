class Solution(object):
    def smallestMissingValueSubtree(self, parents, nums):
        n = len(parents)
        children = [[] for _ in range(n)]
        for i, p in enumerate(parents):
            if p != -1:
                children[p].append(i)

        ans = [1] * n
        idx = -1
        for i, x in enumerate(nums):
            if x == 1:
                idx = i
                break
        if idx == -1:
            return ans

        seen = [False] * (10**5 + 2)
        def dfs(u):
            if not seen[nums[u]]:
                seen[nums[u]] = True
            for v in children[u]:
                dfs(v)

        cur = idx
        missing = 1
        while cur != -1:
            for v in children[cur]:
                if ans[v] == 1:  # not processed yet
                    dfs(v)
            if not seen[nums[cur]]:
                seen[nums[cur]] = True
            while seen[missing]:
                missing += 1
            ans[cur] = missing
            cur = parents[cur]
        return ans
