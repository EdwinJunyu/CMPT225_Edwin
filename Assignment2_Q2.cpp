#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int> > ans;
    sort(nums.begin(), nums.end());
    int n = (int) nums.size();

    for (int i = 0; i < n; ++i) {
        if (i && nums[i] == nums[i - 1]) continue; // filter
        int l = i + 1, r = n - 1;
        while (l < r) {
            int s = nums[i] + nums[l] + nums[r];
            if (s < 0)
                l++;
            else if (s > 0)
                r--;
            else {
                ans.push_back(vector<int>(1, nums[i]));
                ans.back().push_back(nums[l]);
                ans.back().push_back(nums[r]);

                int a = nums[l], b = nums[r]; // two pointer
                while (l < r && nums[l] == a) l++;
                while (l < r && nums[r] == b) r--;
            }
        }
    }
    return ans;  // bigO(O^2)
}
