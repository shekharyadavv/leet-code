# Question: 24. Swap Nodes in Pairs
# Link: https://leetcode.com/problems/swap-nodes-in-pairs/
# Difficulty: Medium
#
# Description:
# Given a linked list, swap every two adjacent nodes and return its head.
# You must solve the problem without modifying the values in the list's
# nodes (i.e., only nodes themselves may be changed).
#
# Example:
# Input:  head = [1,2,3,4]
# Output: [2,1,4,3]
#
# Approach:
# Iterative pointer manipulation using a dummy head node so the first pair
# swap doesn't need special-casing.
# Maintain `prev`, the node right before the current pair. For each pair
# (first, second) = (prev.next, prev.next.next):
#   1. first.next  = second.next   (first now points past the pair)
#   2. second.next = first         (second now points to first)
#   3. prev.next   = second        (prev now points to the new pair head)
#   4. prev = first                (advance prev to the tail of this pair)
# Repeat while there are at least two nodes left after `prev`.
#
# Time Complexity:  O(n) - single pass over the list.
# Space Complexity: O(1) - only a few pointers are used, no recursion.

from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        dummy.next = head
        prev = dummy

        while prev.next and prev.next.next:
            first = prev.next
            second = first.next

            first.next = second.next
            second.next = first
            prev.next = second

            prev = first

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
    print(list_to_str(sol.swapPairs(build_list([1, 2, 3, 4]))))  # 2->1->4->3
    print(list_to_str(sol.swapPairs(build_list([1, 2, 3]))))     # 2->1->3
    print(list_to_str(sol.swapPairs(build_list([]))))            # (empty)
