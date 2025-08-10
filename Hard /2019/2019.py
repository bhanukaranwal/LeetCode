class Solution(object):
    def scoreOfStudents(self, s, answers):
        correct = self.eval_correct(s)
        possible = self.all_possible_results(s)
        score = 0
        for ans in answers:
            if ans == correct:
                score += 5
            elif ans in possible:
                score += 2
        return score

    def eval_correct(self, s):
        nums = []
        ops = []
        i = 0
        while i < len(s):
            if s[i].isdigit():
                nums.append(int(s[i]))
                i += 1
            else:
                ops.append(s[i])
                i += 1
        # First do all multiplications
        stack = [nums[0]]
        for j, op in enumerate(ops):
            if op == '*':
                stack[-1] *= nums[j+1]
            else:
                stack.append(nums[j+1])
        return sum(stack)

    def all_possible_results(self, s):
        n = (len(s) + 1) // 2
        dp = [ [set() for _ in range(n)] for _ in range(n) ]
        nums = [int(s[i]) for i in range(0, len(s), 2)]
        ops = [s[i] for i in range(1, len(s), 2)]
        for i in range(n):
            dp[i][i].add(nums[i])
        for length in range(2, n+1):
            for i in range(n-length+1):
                j = i + length - 1
                for k in range(i, j):
                    for a in dp[i][k]:
                        for b in dp[k+1][j]:
                            if ops[k] == '+':
                                val = a + b
                            else:
                                val = a * b
                            if val <= 1000:
                                dp[i][j].add(val)
        return dp[0][n-1]
