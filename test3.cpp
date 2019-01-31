#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<cmath>
#include<unordered_map>

using namespace std;

int bfind(vector<int>& nums, int n, int target) {
    if (target < nums[0]) {
        return nums[0];
    }
    if (target > nums[n-1]) {
        return nums[n-1];
    }

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
       
        if (nums[mid] >= target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    if (nums[left] - target < target - nums[right]) {
        return nums[left];
    }
    else {
        return nums[right];
    }
}

vector<int> solution(vector<int> stores, vector<int> houses) {
    int m = stores.size();
    int n = houses.size();
    vector<int> ans(n);
    
    sort(stores.begin(), stores.end());

    for (int i = 0; i < n; i++) {
        ans[i] = bfind(stores, m, houses[i]);
    }
    return ans;
}

int main() {
    int tmp1[] = {1, 5, 6, 20, 11, 16};
    int sizetmp1 = sizeof(tmp1) / sizeof(int);
    int tmp2[] = {5, 10, 17};
    int sizetmp2 = sizeof(tmp2) / sizeof(int);
    
    vector<int> stores(tmp1, tmp1+sizetmp1);
    vector<int> houses(tmp2, tmp2+sizetmp2);

    vector<int> ans = solution(stores, houses);

    for (int i = 0; i < ans.size(); i++)
        cout<<ans[i]<<",";
    cout<<endl;

    return 0;
}