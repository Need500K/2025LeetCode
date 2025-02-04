/**
 * 1968. Array With Elements Not Equal to Average of Neighbors
 * 
 * https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/description/
 * 
 * You are given a 0-indexed array nums of distinct integers. 
 * You want to rearrange the elements in the array such that every element in the rearranged array is not equal to the average of its neighbors.
 * More formally, the rearranged array should have the property such that 
 *      for every i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2 is not equal to nums[i].
 * 
 * Return any rearrangement of nums that meets the requirements.
 * 
 * Constraints:
 *      - 3 <= nums.length <= 10^5
 *      - 0 <= nums[i] <= 10^5
 */

/**
 * Example 1:
 *      Input: nums = [1,2,3,4,5]
 *      Output: [1,2,4,5,3]
 *      
 *      Explanation:
 *          When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
 *          When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
 *          When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.
 */

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) 
    {
        int len = nums.size();
        int medianIdx = len / 2;

        // partial sorts nums
        nth_element(nums.begin(), nums.begin() + medianIdx, nums.end());

        int medianValue = nums[medianIdx];

        int smallerIdx = 0;
        int largerIdx = medianIdx + 1;
        vector<int> result(len, 0);
        result[0] = medianValue;

        for (int i = 1; i < len; i+=2)
        {
            result[i]  = nums[smallerIdx++];
        }
        for (int i = 2; i < len; i+=2)
        {
            result[i] = nums[largerIdx++];
        }
        return result;
    }
};
// Solutiuon. 
// Get Median, then place array like [large, median, large, small, large, small ...]
// to become average, neighbors must be set of small and large element compare to N
