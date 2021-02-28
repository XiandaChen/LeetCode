/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
int length(ListNode* cur){
	return !cur ? 0 : length(cur->next) + 1;
}
ListNode* rearrangeLastN(ListNode* l, int n){
	int sz = length(l);
	if (n == 0 || n == sz) return l;
	
	ListNode * newStart = l, *end = l, *prev;
	
	for (int i = 0; i < sz - n; ++i) {
		prev = newStart;
		newStart = newStart->next;
	}
	
	while (end->next) end = end->next;
	
	end->next = l;
	prev->next = nullptr;
	
	return newStart;
}