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

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            
}

int main()
{
    cout<<"test begin"<<endl;

    string input_test = "23";
    cout<<letterCombinations(input_test).size()<<endl;

    return 0;
}