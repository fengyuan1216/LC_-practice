#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>
#include<set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int xxx) {
        val = xxx;
        left = NULL;
        right = NULL;
    }
};


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


TreeNode* buildBST_helper(vector<int>& nums, int begin, int end) {
    if (begin == end) {
        TreeNode* newnode = new TreeNode(nums[begin]);
        return newnode;
    }
    if (begin > end)
        return NULL;

    int mid = begin + (end - begin) / 2;
    TreeNode* newnode = new TreeNode(nums[mid]);
    
    newnode->left = buildBST_helper(nums, begin, mid-1);
    newnode->right = buildBST_helper(nums, mid+1, end);
    return newnode;
}


TreeNode* buildBST(vector<int>& nums) {
    TreeNode* root = buildBST_helper(nums, 0, nums.size()-1);
    return root;
}


void bst_inorder(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> s;
    TreeNode* p = root;

    while (true) {
        if (p != NULL) {
            s.push(p);
            p = p->left;
        }
        else {
            if (s.empty())
                break;
            p = s.top();
            ans.push_back(p->val);
            s.pop();
            p = p->right;
        }
    }

    for (int i = 0; i < ans.size(); i++)
        cout<<ans[i]<<endl;
}


void bst_find_next_helper(TreeNode* p, int target, vector<TreeNode*> onepath, vector<TreeNode*>& path) {
    if (p == NULL)
        return;
    onepath.push_back(p);
    if (p->val == target) {
        path = onepath;
        return;
    }
    bst_find_next_helper(p->left, target, onepath, path);
    bst_find_next_helper(p->right, target, onepath, path);
    return;   
}

void bst_find_next(TreeNode* root, int target) {
    vector<TreeNode*> onepath;
    vector<TreeNode*> path;
    bst_find_next_helper(root, target, onepath, path);

    TreeNode* point = NULL;
    if (path[path.size()-1]->right)
        point = path[path.size()-1]->right;
    else {
        for (int i = path.size()-2; i >= 0; i--) {
            if (path[i]->left == path[i+1]) {
                point = path[i]->right;
                break;
            }
        }
    }

    if (point == NULL)
        cout<<"no next point"<<endl;
    else {
        while (point->left)
            point = point->left;
        cout<<point->val<<endl;
    }

}


void bst_test() {
    vector<int> nums;
    int n = 11;
    for (int i = 0; i < n; i++)
        nums.push_back(i);

    TreeNode* root = buildBST(nums);
    // bst_inorder(root);
    for (int i = 0; i < n; i++)
        bst_find_next(root, i);
}



int cal_upper_bound(vector<int>& nums, int target) {
    int n = nums.size();
    long long left = 0;
    long long right = n-1;
    long long mid;
    long long ans = -1;

    while (left <= right) {
        mid = (left + right) / 2;

        if (nums[mid] == target) {
            ans = mid;
            left = mid+1;
        }
        else if (nums[mid] < target)
            left = mid+1;
        else
            right = mid-1;
    }
    return int(ans);
}

int cal_lower_bound(vector<int>& nums, int target) {
    int n = nums.size();
    long long left = 0;
    long long right = n-1;
    long long mid;
    long long ans = -1;

    while (left <= right) {
        mid = (left + right) / 2;

        if (nums[mid] == target) {
            ans = mid;
            right = mid-1;
        }
        else if (nums[mid] < target)
            left = mid+1;
        else
            right = mid-1;
    }
    return int(ans);
}


int cal_ceiling(vector<int>& nums, int target) {
    int n = nums.size();
    long long left = 0;
    long long right = n-1;
    long long mid;
    long long ans = -1;

    while (left <= right) {
        mid = (left + right) / 2;

        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] > target) {
            ans = mid;
            right = mid-1;
        }
        else
            left = mid+1;
    }
    return ans;
}


int cal_floor(vector<int>& nums, int target) {
    int n = nums.size();
    long long left = 0;
    long long right = n-1;
    long long mid;
    long long ans = -1;

    while (left <= right) {
        mid = (left + right) / 2;

        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            ans = mid;
            left = mid+1;
        }
        else
            right = mid-1;
    }
    return ans;
}


struct datapoint {
    int begin;
    int end;
};


bool cmp(const datapoint& a, const datapoint& b) {
    if (a.begin == b.begin) return a.end < b.end;
    else return a.begin < b.begin;
}



void sorting_test() {
    datapoint dp[5];
    dp[0].begin = 4;
    dp[0].end = 1;
    dp[1].begin = 2;
    dp[1].end = 3;
    dp[2].begin = 9;
    dp[2].end = 10;
    dp[3].begin = 9;
    dp[3].end = 6;
    dp[4].begin = 2;
    dp[5].end = 1;

    vector<datapoint> v;
    for (int i = 0; i < 5; i++)
        v.push_back(dp[i]);

    for (int i = 0; i < 5; i++) {
        cout<<v[i].begin<<","<<v[i].end<<endl;
    }
    cout<<endl;

    sort(v.begin(), v.end(), cmp);

    for (int i = 0; i < 5; i++) {
        cout<<v[i].begin<<","<<v[i].end<<endl;
    }
    cout<<endl;
    
}

void sorting_test2() {
    
}

bool cmp2(const int& a, const int& b) {
    return a > b;
}

string get_lower(string s) {
    int n = s.size();
    vector<int> nums;
    string ans;
    for (int i = 0; i < n; i++)
        nums.push_back(s[i]-'0');

    int index = 1;
    for (int index = 1; index < n; index++) {
        if (nums[index] < nums[index-1])
            break;
    }
    if (index == n) {
        reverse(nums.begin(), nums.end());
        for (int i = 0; i < n; i++)
            ans += to_string(nums[i]);
        return ans;
    }

    for (index = n-1; index >= 1; index--) {
        if (nums[index] < nums[index-1])
            break;
    }
    index--;

    int ref = INT_MIN;
    int index2 = index+1;
    for (int i = index+1; i < n; i++) {
        if (nums[i] < nums[index] && nums[i] > ref) {
            ref = nums[i];
            index2 = i;
        }
    }

    int tmp = nums[index];
    nums[index] = nums[index2];
    nums[index2] = tmp;

    sort(nums.begin()+index+1, nums.end(), cmp2);

    for (int i = 0; i < n; i++)
        ans += to_string(nums[i]);
    return ans;
}



TreeNode* buildtree() {
    TreeNode* root = new TreeNode(1);
    TreeNode* p = root;
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    p->left->left = new TreeNode(4);
    p->left->right = new TreeNode(5);
    p->right->right = new TreeNode(6);
    p->right->right->left = new TreeNode(7);

    return root;
}


TreeNode* find_lca(TreeNode* p, int tar1, int tar2) {
    if (p == NULL) return NULL;
    if (p->val == tar1 || p->val == tar2) return p;

    TreeNode* left = find_lca(p->left, tar1, tar2);
    TreeNode* right = find_lca(p->right, tar1, tar2);

    if (left == NULL && right == NULL) return NULL;
    else if (left != NULL && right == NULL) return left;
    else if (left == NULL && right != NULL) return right;
    else return p;
}

void find_path(TreeNode* p, int tar, vector<TreeNode*>& ans, vector<TreeNode*> path) {
    if (p == NULL) return;
    if (p->val == tar) {
        path.push_back(p);
        ans = path;
        // path.pop_back();
        return;
    }

    path.push_back(p);
    find_path(p->left, tar, ans, path);
    find_path(p->right, tar, ans, path);
    // path.pop_back();
    
    return;
}


void find_node_len() {
    TreeNode* root = buildtree();

    int tar1 = 3;
    int tar2 = 7;

    TreeNode* lca = find_lca(root, tar1, tar2);
    vector<TreeNode*> path;
    vector<TreeNode*> path1;
    vector<TreeNode*> path2;
   
    find_path(root, tar1, path1, path);
    find_path(root, tar2, path2, path);

    for (int i = 0; i < path1.size(); i++)
        cout<<path1[i]->val<<",";
    cout<<endl;

    for (int i = 0; i < path2.size(); i++)
        cout<<path2[i]->val<<",";
    cout<<endl;

    int len = path1.size() + path2.size();
    for (int i = 0; i < min(path1.size(), path2.size()); i++) {
        if (path1[i] == path2[i]) len -= 2;
    }
    len++;

    cout<<len<<endl;
}





void testfunc() {
    string S = "abCi";
    string J = "iyghCay";

    set<char> s;

    for (int i = 0; i < S.size(); i++) {
        s.insert(S[i]);
    }

    int cnt = 0;
    for (int j = 0; j < J.size(); j++) {
        if (s.find(J[j]) != s.end())
            cnt++;
    }
    cout<<cnt<<endl;
}


int main() {
    // find_node_len();
    // testfunc();

    // int test_result1 = Longest_Arithmetic_Progression();
    // cout<<test_result1<<endl;
    // bst_test();
    // vector<int> nums = {1,2,2,2,3,3,3,4,5,6,6,7};
    // int a[] = {1,2,2,2,4,4,5,6,6,7};
    // vector<int> nums;
    // int n = sizeof(a)/sizeof(a[0]);
    // for (int i = 0; i < n; i++)
    //     nums.push_back(a[i]);

    // cout<<cal_lower_bound(nums, 3)<<endl;
    // cout<<cal_upper_bound(nums, 3)<<endl;

    // int target = 8;
    // cout<<cal_floor(nums, target)<<":"<<nums[cal_floor(nums, target)]<<endl;
    // cout<<cal_ceiling(nums, target)<<":"<<nums[cal_ceiling(nums, target)]<<endl;

    // string ss = "4123";
    // string ans = get_lower(ss);
    // cout<<ans<<endl;

    return 0;
}