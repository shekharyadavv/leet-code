# Question: 18. 4Sum
# Link: https://leetcode.com/problems/4sum/
# Difficulty: Medium
#
# Description:
# Given an array nums of n integers, return an array of all the unique
# quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
#   0 <= a, b, c, d < n, a, b, c, d are distinct
#   nums[a] + nums[b] + nums[c] + nums[d] == target
# You may return the answer in any order.
#
# Example:
# Input:  nums = [1,0,-1,0,-2,2], target = 0
# Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
#
# Approach:
# Generalized N-sum reduction via sorting + two pointers:
#   1. Sort the array.
#   2. Fix the first number with an outer loop, the second number with an
#      inner loop, skipping duplicate values at each level so we never
#      generate the same quadruplet twice.
#   3. For the remaining two numbers, use the two-pointer technique on the
#      sorted sub-array: move `left` up / `right` down based on whether the
#      current pair sum is below/above the remaining target.
#   4. Prune branches early: if the smallest possible sum at a given level
#      already exceeds target, break; if the largest possible sum is still
#      below target, skip ahead (continue).
# (Python integers don't overflow, so no special widening is needed here,
# unlike the C++ version which must use long long.)
#
# Time Complexity:  O(n^3) - two nested loops (O(n^2)) + a linear two-pointer
#                    scan (O(n)) for each pair.
# Space Complexity: O(1) extra space, not counting the output array.

from typing import List


class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        result = []

        if n < 4:
            return result

        for i in range(n - 3):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            if nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target:
                break
            if nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target:
                continue

            for j in range(i + 1, n - 2):
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue
                if nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target:
                    break
                if nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target:
                    continue

                left, right = j + 1, n - 1
                need = target - nums[i] - nums[j]

                while left < right:
                    total = nums[left] + nums[right]
                    if total == need:
                        result.append([nums[i], nums[j], nums[left], nums[right]])
                        left += 1
                        right -= 1
                        while left < right and nums[left] == nums[left - 1]:
                            left += 1
                        while left < right and nums[right] == nums[right + 1]:
                            right -= 1
                    elif total < need:
                        left += 1
                    else:
                        right -= 1

        return result


if __name__ == "__main__":
    sol = Solution()
    print(sol.fourSum([1, 0, -1, 0, -2, 2], 0))  # [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
    print(sol.fourSum([2, 2, 2, 2, 2], 8))        # [[2,2,2,2]]
