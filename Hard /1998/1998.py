class Solution(object):
    def gcdSort(self, nums):
        n = len(nums)
        parent = {}

        def find(x):
            parent.setdefault(x, x)
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            parent.setdefault(x, x)
            parent.setdefault(y, y)
            parent[find(x)] = find(y)

        # Sieve for primes up to max(nums)
        max_num = max(nums)
        is_prime = [True] * (max_num + 1)
        primes = []
        limit = int(max_num ** 0.5) + 1
        for i in range(2, limit):
            if is_prime[i]:
                primes.append(i)
                for j in range(i*i, max_num+1, i):
                    is_prime[j] = False
        for i in range(limit, max_num + 1):
            if is_prime[i]:
                primes.append(i)

        # Union each number with its prime factors
        for x in nums:
            num = x
            for p in primes:
                if p * p > num:
                    break
                if num % p == 0:
                    union(x, p)
                    while num % p == 0:
                        num //= p
            if num > 1:
                union(x, num)

        # Check if each number can be swapped to its sorted position
        for x, y in zip(nums, sorted(nums)):
            if find(x) != find(y):
                return False
        return True
