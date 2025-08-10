class Solution:
    def boxDelivering(self, boxes, portsCount, maxBoxes, maxWeight):
        n = len(boxes)
        dp = [0] + [float('inf')] * n
        left = 0
        weight = 0
        trips = 0
        for right in range(n):
            if right == 0 or boxes[right][0] != boxes[right-1][0]:
                trips += 1
            weight += boxes[right][1]
            while (right - left + 1 > maxBoxes or weight > maxWeight or 
                   (left < right and dp[left] == dp[left+1])):
                weight -= boxes[left][1]
                if boxes[left][0] != boxes[left+1][0]:
                    trips -= 1
                left += 1
            dp[right+1] = dp[left] + trips + 1
        return dp[-1]
