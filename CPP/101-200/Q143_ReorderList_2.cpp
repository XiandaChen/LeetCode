class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) { // second half
            slow = slow->next;
            fast = fast->next->next; // ->next->next
        }
        ListNode * firsthalf = head;
        ListNode * secondhalf = reverseList(slow); // reverse linkedlist
        while (firsthalf && secondhalf) {
            ListNode * tmp = firsthalf->next;
            firsthalf->next = secondhalf;
            secondhalf = secondhalf->next;
            firsthalf->next->next = tmp;  // link newnode to oldlist
            firsthalf = tmp;                 // move head to oldhead->next
        }
        if (firsthalf) // set last node's next to NULL
            firsthalf->next = NULL;
    }
    
    ListNode * reverseList(ListNode * head) {
        ListNode * newhead = NULL;
        while (head) {
            ListNode * tmp = head->next;
            head->next = newhead;
            newhead = head;
            head = tmp;
        }
        return newhead;
    }
};
