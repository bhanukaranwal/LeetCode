/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * ListNode *next;
 * ListNode() : val(0), next(nullptr) {}
 * ListNode(int x) : val(x), next(nullptr) {}
 * ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 1. Check if there are at least k nodes left.
        ListNode* cursor = head;
        for (int i = 0; i < k; ++i) {
            if (cursor == nullptr) {
                // If not, the remaining part is left as is.
                return head;
            }
            cursor = cursor->next;
        }

        // 2. Reverse the k nodes.
        ListNode* prev = nullptr;
        ListNode* current = head;
        for (int i = 0; i < k; ++i) {
            ListNode* next_node = current->next;
            current->next = prev;
            prev = current;
            current = next_node;
        }

        // 3. After reversing, `head` is the new tail of this group.
        // `current` is the head of the next group.
        // Connect the new tail to the result of the recursive call.
        head->next = reverseKGroup(current, k);
        
        // `prev` is the new head of the reversed group.
        return prev;
    }
};
