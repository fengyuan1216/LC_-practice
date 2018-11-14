#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>

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






int main() {
    // int test_result1 = Longest_Arithmetic_Progression();
    // cout<<test_result1<<endl;
    bst_test();
    return 0;
}