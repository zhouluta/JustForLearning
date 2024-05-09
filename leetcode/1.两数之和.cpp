/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
#include <vector>
#include <unordered_set>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_set<int> seen;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (seen.find(complement) != seen.end()) {
            return {seen.find(complement), i};
        }
        seen.insert(nums[i]);
    }
    return {};
}
// @lc code=end

