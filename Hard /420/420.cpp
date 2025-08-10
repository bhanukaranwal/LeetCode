class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.size();
        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        int missingTypes = (!hasLower) + (!hasUpper) + (!hasDigit);

        int replace = 0, one = 0, two = 0;
        for (int i = 2; i < n;) {
            if (password[i] == password[i-1] && password[i-1] == password[i-2]) {
                int len = 2;
                while (i < n && password[i] == password[i-1]) {
                    ++len; ++i;
                }
                replace += len / 3;
                if (len % 3 == 0) ++one;
                else if (len % 3 == 1) ++two;
            } else {
                ++i;
            }
        }

        if (n < 6)
            return max(missingTypes, 6 - n);
        else if (n <= 20)
            return max(missingTypes, replace);

        int del = n - 20;
        int rem = del;

        // First remove from (3k) groups
        int use = min(one, rem);
        replace -= use;
        rem -= use;

        // Then remove from (3k+1) groups
        use = min(two * 2, rem);
        replace -= use / 2;
        rem -= use;

        // Then remove from (3k+2) groups
        replace -= rem / 3;

        return del + max(missingTypes, replace);
    }
};
