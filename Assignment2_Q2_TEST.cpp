#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int> > ans;
        sort(nums.begin(), nums.end());
        int n = (int) nums.size();

        for (int i = 0; i < n; ++i) {
            if (i && nums[i] == nums[i - 1]) continue;
            int l = i + 1, r = n - 1;
            while (l < r) {
                int s = nums[i] + nums[l] + nums[r];
                if (s < 0) ++l;
                else if (s > 0) r--;
                else {
                    ans.push_back(vector<int>(1, nums[i]));
                    ans.back().push_back(nums[l]);
                    ans.back().push_back(nums[r]);

                    int a = nums[l], b = nums[r];
                    while (l < r && nums[l] == a) l++;
                    while (l < r && nums[r] == b) r--;
                }
            }
        }
        return ans;
    }
};
static void printVec(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

static void printTriplets(const vector<vector<int> >& trips) {
    cout << "[\n";
    for (int i = 0; i < (int)trips.size(); ++i) {
        cout << "  ";
        printVec(trips[i]);
        cout << "\n";
    }
    cout << "]\n";
}

int main() {
    Solution sol;

    // 测试1：经典例子
    vector<int> nums1;
    nums1.push_back(-1);
    nums1.push_back(0);
    nums1.push_back(1);
    nums1.push_back(2);
    nums1.push_back(-1);
    nums1.push_back(-4);
    cout << "Test 1 nums = ";
    printVec(nums1);
    cout << "\nTriplets:\n";
    printTriplets(sol.threeSum(nums1));
    cout << "\n";

    // 测试2：全0
    vector<int> nums2;
    nums2.push_back(0);
    nums2.push_back(0);
    nums2.push_back(0);
    nums2.push_back(0);
    cout << "Test 2 nums = ";
    printVec(nums2);
    cout << "\nTriplets:\n";
    printTriplets(sol.threeSum(nums2));
    cout << "\n";

    // 测试3：没有解
    vector<int> nums3;
    nums3.push_back(1);
    nums3.push_back(2);
    nums3.push_back(-2);
    nums3.push_back(-1);
    cout << "Test 3 nums = ";
    printVec(nums3);
    cout << "\nTriplets:\n";
    printTriplets(sol.threeSum(nums3));
    cout << "\n";

    // 测试4：包含重复值的更多情况
    vector<int> nums4;
    nums4.push_back(-2);
    nums4.push_back(0);
    nums4.push_back(0);
    nums4.push_back(2);
    nums4.push_back(2);
    cout << "Test 4 nums = ";
    printVec(nums4);
    cout << "\nTriplets:\n";
    printTriplets(sol.threeSum(nums4));
    cout << "\n";

    // 测试5：边界（长度<3）
    vector<int> nums5;
    nums5.push_back(0);
    nums5.push_back(1);
    cout << "Test 5 nums = ";
    printVec(nums5);
    cout << "\nTriplets:\n";
    printTriplets(sol.threeSum(nums5));
    cout << "\n";

    return 0;
}