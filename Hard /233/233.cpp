class Solution {
public:
    int countDigitOne(int n) {
        int count = 0;

        // We iterate through each place value: 1s, 10s, 100s, etc.
        // 'm' represents the current place value (1, 10, 100, ...).
        for (long long m = 1; m <= n; m *= 10) {
            // Split n into two parts around the current place value 'm'.
            // 'a' is the part to the left, 'b' is the part to the right.
            long long a = n / m;
            long long b = n % m;

            // This line calculates the number of '1's from full blocks.
            // For example, if we are at the 10s place (m=10) and n=2345,
            // this counts all the '1's in the 10s place for numbers up to 2299.
            // The (a + 8) / 10 trick is a concise way to handle this.
            count += (a + 8) / 10 * m;

            // This handles the '1's in the last, partial block.
            // For example, if n=2315 and m=10, we are looking at the range 2300-2315.
            // The digit at the 10s place is 1, so we add the count for 2310-2315, which is b+1.
            if (a % 10 == 1) {
                count += b + 1;
            }
        }

        return count;
    }
};
