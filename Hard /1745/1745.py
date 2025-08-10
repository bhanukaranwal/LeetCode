class Solution(object):
    def checkPartitioning(self, s):
        n = len(s)
        # Precompute palindrome substrings
        is_pal = [[False] * n for _ in range(n)]
        for l in range(n):
            for i in range(n - l):
                j = i + l
                if s[i] == s[j] and (l < 2 or is_pal[i+1][j-1]):
                    is_pal[i][j] = True

        # Try all possible splits: s[0:i], s[i:j], s[j:]
        for i in range(1, n-1):
            for j in range(i+1, n):
                if is_pal[0][i-1] and is_pal[i][j-1] and is_pal[j][n-1]:
                    return True
        return False
