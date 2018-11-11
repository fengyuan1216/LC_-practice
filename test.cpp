#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>

using namespace std;

void dfs(vector<int>& p_num, vector<int>& ans, int val, int start_index, int n) {
    if (start_index == n)
        return;

    int cur = val * p_num[start_index];
    ans.push_back(cur);
    for (int i = start_index + 1; i < n; i++) {
        dfs(p_num, ans, cur, i, n);
    }
}

int main() {
    // int s[] = {1,-9,3,0,5};
    int s[] = {1,2,3,4,5};

    int n = sizeof(s) / sizeof(s[0]);
    // cout<<n<<endl;

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

    cout<<"first result: ";
    cout<<max_len<<endl<<endl;
    cout<<"second result: "<<endl;

    ///////////////////////////////

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

    cout<<max_len<<endl;

    

    // unordered_map<int, int>::iterator it;
    // for (int i = 0; i < n; i++) {
    //     for (it = dp[i].begin(); it != dp[i].end(); it++) {
    //         cout<<it->first<<", "<<it->second<<endl;
    //     }
    // }



    
    // prime_num.push_back(7);
    // prime_num.push_back(11);

    // vector<int> ans;
    // for (int i = 0; i < prime_num.size(); i++)
    //     dfs(prime_num, ans, 1, i, prime_num.size());

    // vector<int>::iterator it;
    // for (it = ans.begin(); it != ans.end(); it++)
    //     cout<<*it<<endl;

    // string tmp = "abc";
    // cout<<tmp.length()<<endl;
    // cout<<tmp.size()<<endl;

    return 0;
}