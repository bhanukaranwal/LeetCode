from collections import Counter

class Solution(object):
    def longestSubsequenceRepeatedK(self, s, k):
        freq = Counter(s)
        chars = [c for c in freq if freq[c] >= k]
        chars.sort(reverse=True)  # for lexicographically largest

        def can_build(candidate):
            cnt = Counter(candidate)
            for c in cnt:
                if cnt[c] * k > freq[c]:
                    return False
            return True

        def is_k_repeated_subseq(candidate):
            t = ''.join(candidate) * k
            i = 0
            for c in s:
                if c == t[i]:
                    i += 1
                    if i == len(t):
                        return True
            return False

        max_len = len(s) // k
        # BFS: try longer strings first, lexicographically largest first
        from collections import deque
        queue = deque([''])
        ans = ''
        while queue:
            cur = queue.popleft()
            if len(cur) > max_len:
                continue
            for c in chars:
                nxt = cur + c
                if can_build(nxt):
                    if is_k_repeated_subseq(nxt):
                        if len(nxt) > len(ans) or (len(nxt) == len(ans) and nxt > ans):
                            ans = nxt
                        queue.append(nxt)
        return ans
