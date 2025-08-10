import java.util.*;

class FreqStack {
    // Map from value to its frequency
    private Map<Integer, Integer> freq;
    // Map from frequency to a stack of values with that frequency
    private Map<Integer, Stack<Integer>> group;
    // Track the current maximum frequency
    private int maxFreq;

    public FreqStack() {
        freq = new HashMap<>();
        group = new HashMap<>();
        maxFreq = 0;
    }
    
    public void push(int val) {
        int f = freq.getOrDefault(val, 0) + 1;
        freq.put(val, f);
        if (!group.containsKey(f)) group.put(f, new Stack<>());
        group.get(f).push(val);
        if (f > maxFreq) maxFreq = f;
    }
    
    public int pop() {
        Stack<Integer> stack = group.get(maxFreq);
        int val = stack.pop();
        freq.put(val, freq.get(val) - 1);
        if (stack.isEmpty()) maxFreq--;
        return val;
    }
}
