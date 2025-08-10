import java.util.*;

class Solution {
    public int oddEvenJumps(int[] arr) {
        int n = arr.length;
        int[] nextHigher = new int[n];
        int[] nextLower = new int[n];

        // Prepare nextHigher (odd jumps)
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; ++i) idx[i] = i;
        Arrays.sort(idx, (a, b) -> arr[a] == arr[b] ? a - b : arr[a] - arr[b]);
        Stack<Integer> stack = new Stack<>();
        for (int i : idx) {
            while (!stack.isEmpty() && i > stack.peek()) {
                nextHigher[stack.pop()] = i;
            }
            stack.push(i);
        }

        // Prepare nextLower (even jumps)
        Arrays.sort(idx, (a, b) -> arr[a] == arr[b] ? a - b : arr[b] - arr[a]);
        stack.clear();
        for (int i : idx) {
            while (!stack.isEmpty() && i > stack.peek()) {
                nextLower[stack.pop()] = i;
            }
            stack.push(i);
        }

        boolean[] odd = new boolean[n];
        boolean[] even = new boolean[n];
        odd[n - 1] = even[n - 1] = true;

        for (int i = n - 2; i >= 0; --i) {
            if (nextHigher[i] != 0) odd[i] = even[nextHigher[i]];
            if (nextLower[i] != 0) even[i] = odd[nextLower[i]];
        }

        int res = 0;
        for (boolean b : odd) if (b) res++;
        return res;
    }
}
