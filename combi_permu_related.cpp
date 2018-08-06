#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>

using namespace std;


void letterCombinations_dfs(string digits, int current_index, string current_str, vector<string> digit_to_str, vector<string> &digit_str){
    if (current_index >= digits.length())
        digit_str.push_back(current_str);
    else{
        string current_digit_str = digit_to_str[digits[current_index] - '0'];
        if (current_digit_str.length() == 0)
            letterCombinations_dfs(digits, current_index + 1, current_str, digit_to_str, digit_str);
        else{
            for (int i = 0; i < current_digit_str.length(); i++)
                letterCombinations_dfs(digits, current_index + 1, current_str + current_digit_str[i], digit_to_str, digit_str);
        }
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> digit_to_str;
    digit_to_str.push_back("");
    digit_to_str.push_back("");
    digit_to_str.push_back("abc");
    digit_to_str.push_back("def");
    digit_to_str.push_back("ghi");
    digit_to_str.push_back("jkl");
    digit_to_str.push_back("mno");
    digit_to_str.push_back("pqrs");
    digit_to_str.push_back("tuv");
    digit_to_str.push_back("wxyz");

    vector<string> digit_str;
    if (digits.length() == 0)
        return digit_str;
    
    letterCombinations_dfs(digits, 0, "", digit_to_str, digit_str);
    return digit_str;
}

void nextPermutation(vector<int>& nums) {
    int pos1 = -1;
    for (int i = nums.size() - 2; i >= 0; --i){
        if (nums[i + 1] > nums[i]){
            pos1 = i;
            break;
        }
    }
    if (pos1 != -1){
        int pos2 =  - 1;
        for (pos2 = nums.size() - 1; pos2 > pos1; pos2--){
            if (nums[pos2] > nums[pos1])
                break;
        }
        int tmp = nums[pos1];
        nums[pos1] = nums[pos2];
        nums[pos2] = tmp;
        sort(nums.begin() + pos1 + 1, nums.end());
    }
    else
        sort(nums.begin(), nums.end());
}

vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
    vector<vector<int> > answer;
    vector<int> one_answer;
    combinationSum_helper(answer, candidates, one_answer, target, 0);
    return answer;
}

void combinationSum_helper(vector<vector<int> >& answer_combi, vector<int>& candidates, vector<int> one_answer, int target, int index) {
    if (target == 0) {
        answer_combi.push_back(one_answer);
        return;
    }
    else {
        for (int i = index; i < candidates.size(); i++) {
            if (target - candidates[i] >= 0) {
                one_answer.push_back(candidates[i]);
                combinationSum_helper(answer_combi, candidates, one_answer, target - candidates[i], i);
                one_answer.pop_back();
            }
        }
        return;
    }
}


vector<vector<int> > combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int> > answer;
    vector<int> one_answer;
    sort(candidates.begin(), candidates.end());
    combinationSum_helper2(answer, candidates, one_answer, target, 0);
    return answer;
}

void combinationSum_helper2(vector<vector<int> >& answer_combi, vector<int>& candidates, vector<int> one_answer, int target, int index) {
    if (target == 0) {
        answer_combi.push_back(one_answer);
        return;
    }
    else {
        for (int i = index; i < candidates.size(); i++) {
            if (target - candidates[i] >= 0) {
                one_answer.push_back(candidates[i]);
                combinationSum_helper2(answer_combi, candidates, one_answer, target - candidates[i], i + 1);
                one_answer.pop_back();
            }
            while ((i + 1 < candidates.size()) && (candidates[i + 1] == candidates[i])) {
                i++;
            }
        }
        return;
    }
}



int main()
{
    cout<<"test begin"<<endl;

    string input_test = "23";
    
    int x = -1;
    int y = 4;
    cout<<(x/y)<<endl;

    return 0;
}