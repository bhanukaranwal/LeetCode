class Solution(object):
    def smallestSubsequence(self, s, k, letter, repetition):
        n = len(s)
        count_letter = s.count(letter)
        stack = []
        letters_in_stack = 0 

        for i, c in enumerate(s):
            
            remain = n - i - 1
           
            need = k - len(stack)
            
            rep_left = repetition - letters_in_stack
           
            while stack and c < stack[-1] and len(stack) + remain >= k:
               
                if stack[-1] == letter:
                    if letters_in_stack + count_letter - (stack[-1] == letter) >= repetition:
                        stack.pop()
                        letters_in_stack -= 1
                    else:
                        break
                else:
                    stack.pop()
           
            if len(stack) < k:
                if c == letter:
                    stack.append(c)
                    letters_in_stack += 1
                else:
                    
                    if k - len(stack) > repetition - letters_in_stack:
                        stack.append(c)
           
            if c == letter:
                count_letter -= 1

        
        res = []
        cnt = 0
        for c in stack:
            if c == letter:
                cnt += 1
            res.append(c)
       
        i = len(res) - 1
        while cnt < repetition:
            if res[i] != letter:
                res[i] = letter
                cnt += 1
            i -= 1
        return ''.join(res)
