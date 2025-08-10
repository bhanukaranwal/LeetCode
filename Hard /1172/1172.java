import java.util.*;

class DinnerPlates {
    private int capacity;
    private List<Stack<Integer>> stacks;
    private PriorityQueue<Integer> available; // min-heap for leftmost available stack
    private int rightmost; // index of rightmost non-empty stack

    public DinnerPlates(int capacity) {
        this.capacity = capacity;
        this.stacks = new ArrayList<>();
        this.available = new PriorityQueue<>();
        this.rightmost = -1;
    }

    public void push(int val) {
        // Clean up available heap
        while (!available.isEmpty() && available.peek() < stacks.size() && stacks.get(available.peek()).size() == capacity)
            available.poll();
        int idx;
        if (!available.isEmpty()) {
            idx = available.peek();
        } else {
            idx = stacks.size();
            stacks.add(new Stack<>());
        }
        stacks.get(idx).push(val);
        if (stacks.get(idx).size() < capacity)
            available.offer(idx);
        if (idx > rightmost) rightmost = idx;
    }

    public int pop() {
        while (rightmost >= 0 && (rightmost >= stacks.size() || stacks.get(rightmost).isEmpty()))
            rightmost--;
        if (rightmost < 0) return -1;
        int val = stacks.get(rightmost).pop();
        available.offer(rightmost);
        return val;
    }

    public int popAtStack(int index) {
        if (index >= stacks.size() || stacks.get(index).isEmpty()) return -1;
        int val = stacks.get(index).pop();
        available.offer(index);
        if (index == rightmost) {
            while (rightmost >= 0 && (rightmost >= stacks.size() || stacks.get(rightmost).isEmpty()))
                rightmost--;
        }
        return val;
    }
}
