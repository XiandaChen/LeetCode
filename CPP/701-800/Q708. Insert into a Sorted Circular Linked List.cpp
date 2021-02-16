/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (!head) { // empty list
            head = new Node(insertVal, NULL);
            head->next = head;
            return head;
        }
        Node* pre = head, *cur = head->next;
        while (cur != head) {
            if (pre->val <= insertVal && insertVal <= cur->val) break; 
            // insert b/w max and min: [3,4,1] -> [3,4,5,1]
            if (pre->val > cur->val && (insertVal >= pre->val || insertVal <= cur->val)) break;
            pre = cur;
            cur = cur->next;
        }
        pre->next = new Node(insertVal, cur);
        return head;
    }
};