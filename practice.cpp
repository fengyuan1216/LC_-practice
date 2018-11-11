#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>

using namespace std;


int Longest_Arithmetic_Progression() {
    bool brute_force = false;
    bool use_dp = true;

    int s[] = {1,2,3,4,5};
    int n = sizeof(s) / sizeof(s[0]);
    vector<int> nums;
    for (int i = 0; i < n; i++)
        nums.push_back(s[i]);

    int max_len = 0;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    
    max_len = 2;

    if (brute_force) {
        for (int i = 0; i < n-2; i++) {
            for (int j = i+1; j < n-1; j++) {
                int tmp_gap = nums[j] - nums[i];
                int cur_val = nums[j];
                int cnt = 2;

                for (int k = j+1; k < n; k++) {
                    if (nums[k] - cur_val == tmp_gap) {
                        cnt++;
                        cur_val = nums[k];
                    }
                }
                max_len = max(max_len, cnt);
            }
        }
        return max_len;
    }
    
    if (use_dp) {
        vector<unordered_map<int, int> > dp(n); //distance, cnt

        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }

        max_len = 0;

        for (int i = n-2; i >= 0; i--) {
            for (int j = i+1; j < n; j++) {
                int gap = nums[j] - nums[i];

                if (dp[j].find(gap) != dp[j].end()) {
                    dp[i][gap] = dp[j][gap] + 1;
                } 
                else {
                    dp[i][gap] = 2;
                }

                max_len = max(max_len, dp[i][gap]);
            }
        }
        return max_len;
    }

    return max_len;
}



int main() {
    int test_result1 = Longest_Arithmetic_Progression();

    cout<<test_result1<<endl;

    return 0;
}