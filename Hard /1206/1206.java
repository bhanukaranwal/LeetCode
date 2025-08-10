import java.util.*;

class Skiplist {
    static class Node {
        int val;
        Node[] next;
        Node(int val, int level) {
            this.val = val;
            this.next = new Node[level];
        }
    }

    private static final int MAX_LEVEL = 16;
    private static final double P = 0.5;
    private Node head;
    private Random rand;

    public Skiplist() {
        head = new Node(-1, MAX_LEVEL);
        rand = new Random();
    }

    // Helper to find predecessors at each level for a value
    private Node[] find(int target) {
        Node[] update = new Node[MAX_LEVEL];
        Node curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (curr.next[i] != null && curr.next[i].val < target) {
                curr = curr.next[i];
            }
            update[i] = curr;
        }
        return update;
    }

    public boolean search(int target) {
        Node curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--) {
            while (curr.next[i] != null && curr.next[i].val < target) {
                curr = curr.next[i];
            }
        }
        curr = curr.next[0];
        return curr != null && curr.val == target;
    }

    public void add(int num) {
        Node[] update = find(num);
        int level = randomLevel();
        Node newNode = new Node(num, level);
        for (int i = 0; i < level; i++) {
            newNode.next[i] = update[i].next[i];
            update[i].next[i] = newNode;
        }
    }

    public boolean erase(int num) {
        Node[] update = find(num);
        Node curr = update[0].next[0];
        if (curr == null || curr.val != num) return false;
        for (int i = 0; i < curr.next.length; i++) {
            update[i].next[i] = curr.next[i];
        }
        return true;
    }

    // Randomly choose level for new node
    private int randomLevel() {
        int level = 1;
        while (level < MAX_LEVEL && rand.nextDouble() < P) level++;
        return level;
    }
}
