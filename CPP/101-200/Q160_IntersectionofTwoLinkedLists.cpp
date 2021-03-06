/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return NULL;
        int lenA = getLength(headA), lenB = getLength(headB);
        if (lenA < lenB) {
            for (int i = 0; i < (lenB - lenA); ++i)
                headB = headB->next;
        }
        else {
            for (int i = 0; i < (lenA - lenB); ++i)
                headA = headA->next;
        }
        while (headA && headB) {
            if (headA == headB) return headA;
            headA = headA->next;
            headB = headB->next;
        }
        return NULL;
    }
    int getLength (ListNode * head) {
        int cnt = 0;
        while (head) {
            ++cnt;
            head = head->next;
        }
        return cnt;
    }
};