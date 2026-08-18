# Question: 23. Merge k Sorted Lists
# Link: https://leetcode.com/problems/merge-k-sorted-lists/
# Difficulty: Hard
#
# Description:
# You are given an array of k linked-lists `lists`, each linked-list is
# sorted in ascending order. Merge all the linked-lists into one sorted
# linked-list and return it.
#
# Example:
# Input:  lists = [[1,4,5],[1,3,4],[2,6]]
# Output: [1,1,2,3,4,4,5,6]
#
# Approach:
# Classic k-way merge using a min-heap (heapq):
#   1. Push (value, unique_index, node) for the head of every non-empty list
#      into a min-heap. The `unique_index` tiebreaker avoids Python trying
#      to compare ListNode objects directly when two values are equal.
#   2. Repeatedly pop the smallest entry, append its node to the output
#      list, and if that node has a `next`, push it into the heap.
#   3. Continue until the heap is empty; the output list is the fully
#      merged, sorted list.
#
# Time Complexity:  O(N log k) - N = total number of nodes across all
#                    lists, k = number of lists. Each node is pushed and
#                    popped from a heap of size <= k exactly once.
# Space Complexity: O(k) for the heap (plus O(1) extra beyond that, reusing
#                    existing nodes rather than allocating new ones).

import heapq
from typing import List, Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = []
        counter = 0  # tiebreaker so heapq never has to compare ListNode objects

        for node in lists:
            if node:
                heapq.heappush(heap, (node.val, counter, node))
                counter += 1

        dummy = ListNode(0)
        tail = dummy

        while heap:
            val, _, smallest = heapq.heappop(heap)
            tail.next = smallest
            tail = tail.next

            if smallest.next:
                heapq.heappush(heap, (smallest.next.val, counter, smallest.next))
                counter += 1

        tail.next = None
        return dummy.next


# --- Small helper harness for local testing (not required by LeetCode) ---
def build_list(vals):
    dummy = ListNode(0)
    tail = dummy
    for v in vals:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next


def list_to_str(head):
    vals = []
    while head:
        vals.append(str(head.val))
        head = head.next
    return "->".join(vals) if vals else "(empty)"


if __name__ == "__main__":
    sol = Solution()
    lists = [build_list([1, 4, 5]), build_list([1, 3, 4]), build_list([2, 6])]
    print(list_to_str(sol.mergeKLists(lists)))  # 1->1->2->3->4->4->5->6
