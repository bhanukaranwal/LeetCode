def nCr(n, r):
    # Efficient computation of n choose r
    if r < 0 or r > n:
        return 0
    res = 1
    for i in range(1, r+1):
        res = res * (n - r + i) // i
    return res

class Solution(object):
    def kthSmallestPath(self, destination, k):
        row, col = destination
        res = []
        for _ in range(row + col):
            if col == 0:
                res.append('V')
                row -= 1
            elif row == 0:
                res.append('H')
                col -= 1
            else:
                h_first = nCr(row + col - 1, col - 1)
                if k <= h_first:
                    res.append('H')
                    col -= 1
                else:
                    res.append('V')
                    k -= h_first
                    row -= 1
        return ''.join(res)
