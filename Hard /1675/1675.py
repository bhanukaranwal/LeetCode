import heapq

class Solution(object):
    def minimumDeviation(self, nums):
        # Step 1: Make all numbers even (multiply odds by 2)
        heap = []
        min_num = float('inf')
        for num in nums:
            if num % 2:
                num *= 2
            heap.append(-num)  # max-heap by using negatives
            min_num = min(min_num, num)
        
        heapq.heapify(heap)
        res = float('inf')
        
        # Step 2: Try to minimize deviation by reducing the max element
        while True:
            max_num = -heapq.heappop(heap)
            res = min(res, max_num - min_num)
            if max_num % 2 == 0:
                next_num = max_num // 2
                min_num = min(min_num, next_num)
                heapq.heappush(heap, -next_num)
            else:
                break  # Can't reduce further if max is odd
        return res
