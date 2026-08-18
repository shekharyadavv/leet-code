// Question: 23. Merge k Sorted Lists
// Link: https://leetcode.com/problems/merge-k-sorted-lists/
// Difficulty: Hard
//
// Description:
// You are given an array of k linked-lists `lists`, each linked-list is
// sorted in ascending order. Merge all the linked-lists into one sorted
// linked-list and return it.
//
// Example:
// Input:  lists = [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
//
// Approach:
// Classic k-way merge using a min-heap (priority_queue):
//   1. Push the head node of every non-empty list into a min-heap ordered
//      by node value.
//   2. Repeatedly pop the smallest node from the heap, append it to the
//      output list, and if that node has a `next`, push the next node into
//      the heap.
//   3. Continue until the heap is empty; the output list is the fully
//      merged, sorted list.
// This avoids the O(k) linear scan per node that a naive "compare all heads"
// approach would need, since the heap keeps the current minimum at the top
// in O(log k).
//
// Time Complexity:  O(N log k) - N = total number of nodes across all
//                    lists, k = number of lists. Each node is pushed and
//                    popped from a heap of size <= k exactly once.
// Space Complexity: O(k) for the heap (plus O(1) extra beyond that,
//                    reusing existing nodes rather than allocating new ones).

#include <vector>
#include <queue>
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
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val; // min-heap: smallest value has highest priority
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        for (ListNode* node : lists) {
            if (node) pq.push(node);
        }

        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (!pq.empty()) {
            ListNode* smallest = pq.top();
            pq.pop();

            tail->next = smallest;
            tail = tail->next;

            if (smallest->next) pq.push(smallest->next);
        }

        tail->next = nullptr;
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
    vector<ListNode*> lists = {
        buildList({1, 4, 5}),
        buildList({1, 3, 4}),
        buildList({2, 6})
    };
    printList(sol.mergeKLists(lists)); // expected: 1->1->2->3->4->4->5->6
    return 0;
}
