// Question: 24. Swap Nodes in Pairs
// Link: https://leetcode.com/problems/swap-nodes-in-pairs/
// Difficulty: Medium
//
// Description:
// Given a linked list, swap every two adjacent nodes and return its head.
// You must solve the problem without modifying the values in the list's
// nodes (i.e., only nodes themselves may be changed).
//
// Example:
// Input:  head = [1,2,3,4]
// Output: [2,1,4,3]
//
// Approach:
// Iterative pointer manipulation using a dummy head node so the first pair
// swap doesn't need special-casing.
// Maintain `prev`, the node right before the current pair. For each pair
// (first, second) = (prev->next, prev->next->next):
//   1. first->next  = second->next   (first now points past the pair)
//   2. second->next = first          (second now points to first)
//   3. prev->next   = second         (prev now points to the new pair head)
//   4. prev = first                  (advance prev to the tail of this pair)
// Repeat while there are at least two nodes left after `prev`.
//
// Time Complexity:  O(n) - single pass over the list.
// Space Complexity: O(1) - only a few pointers are used, no recursion.

#include <vector>
using namespace std;

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
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        while (prev->next && prev->next->next) {
            ListNode* first = prev->next;
            ListNode* second = first->next;

            first->next = second->next;
            second->next = first;
            prev->next = second;

            prev = first;
        }
        return dummy.next;
    }
};

// --- Small helper harness for local testing (not required by LeetCode) ---
#include <iostream>
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << "->";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;
    ListNode* l1 = buildList({1, 2, 3, 4});
    printList(sol.swapPairs(l1)); // expected: 2->1->4->3

    ListNode* l2 = buildList({1, 2, 3});
    printList(sol.swapPairs(l2)); // expected: 2->1->3

    ListNode* l3 = buildList({});
    printList(sol.swapPairs(l3)); // expected: (empty)
    return 0;
}
