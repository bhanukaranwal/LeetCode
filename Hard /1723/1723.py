class Solution(object):
    def minimumTimeRequired(self, jobs, k):
        jobs.sort(reverse=True)
        n = len(jobs)
        
        def can_assign(limit):
            workers = [0] * k
            def backtrack(i):
                if i == n:
                    return True
                seen = set()
                for w in range(k):
                    if workers[w] + jobs[i] <= limit and workers[w] not in seen:
                        workers[w] += jobs[i]
                        if backtrack(i + 1):
                            return True
                        workers[w] -= jobs[i]
                        seen.add(workers[w])
                    if workers[w] == 0:
                        break  # Don't assign the same job to multiple empty workers
                return False
            return backtrack(0)
        
        left, right = max(jobs), sum(jobs)
        while left < right:
            mid = (left + right) // 2
            if can_assign(mid):
                right = mid
            else:
                left = mid + 1
        return left
