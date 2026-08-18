// Question: 18. 4Sum
// Link: https://leetcode.com/problems/4sum/
// Difficulty: Medium
//
// Description:
// Given an array nums of n integers, return an array of all the unique
// quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
//   0 <= a, b, c, d < n, a, b, c, d are distinct
//   nums[a] + nums[b] + nums[c] + nums[d] == target
// You may return the answer in any order.
//
// Example:
// Input:  nums = [1,0,-1,0,-2,2], target = 0
// Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
//
// Approach:
// Generalized N-sum reduction via sorting + two pointers:
//   1. Sort the array.
//   2. Fix the first number with an outer loop, the second number with an
//      inner loop, skipping duplicate values at each level so we never
//      generate the same quadruplet twice.
//   3. For the remaining two numbers, use the two-pointer technique on the
//      sorted sub-array: move `left` up / `right` down based on whether the
//      current pair sum is below/above the remaining target.
//   4. Prune branches early: if the smallest possible sum at a given level
//      already exceeds target, break; if the largest possible sum is still
//      below target, skip ahead (continue).
// Values are cast to `long long` throughout because nums[i] and target can
// each be up to 1e9 in magnitude, so a sum of four can overflow a 32-bit int.
//
// Time Complexity:  O(n^3) - two nested loops (O(n^2)) + a linear two-pointer
//                    scan (O(n)) for each pair.
// Space Complexity: O(1) extra space, not counting the output array
//                    (O(log n) to O(n) for the sort's internal stack, and
//                    O(n) for the output itself).

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 4) return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            if ((long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
            if ((long long)nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue;

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                if ((long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
                if ((long long)nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target) continue;

                int left = j + 1, right = n - 1;
                long long need = (long long)target - nums[i] - nums[j];

                while (left < right) {
                    long long sum = (long long)nums[left] + nums[right];
                    if (sum == need) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        left++;
                        right--;
                        while (left < right && nums[left] == nums[left - 1]) left++;
                        while (left < right && nums[right] == nums[right + 1]) right--;
                    } else if (sum < need) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return result;
    }
};

// --- Small helper harness for local testing (not required by LeetCode) ---
#include <iostream>
int main() {
    Solution sol;
    vector<int> nums1 = {1, 0, -1, 0, -2, 2};
    auto res1 = sol.fourSum(nums1, 0);
    for (auto& quad : res1) {
        cout << "[";
        for (size_t k = 0; k < quad.size(); k++) cout << quad[k] << (k + 1 < quad.size() ? "," : "");
        cout << "] ";
    }
    cout << endl; // expected: [-2,-1,1,2] [-2,0,0,2] [-1,0,0,1]
    return 0;
}
