#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> nextGreaterElements(std::vector<int> &nums)
    {
        std::stack<std::pair<int, int>> stack;
        std::vector<int> ans(nums.size(), -1);
        for (int i = 0; i < nums.size(); ++i)
        {
            while (!stack.empty() && stack.top().first < nums[i])
            {
                ans[stack.top().second] = nums[i];
                stack.pop();
            }

            stack.emplace(nums[i], i);
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            while (!stack.empty() && stack.top().first < nums[i])
            {
                ans[stack.top().second] = nums[i];
                stack.pop();
            }
        }

        return ans;
    }
};
