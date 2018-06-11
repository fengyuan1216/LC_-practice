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


int main()
{
    cout<<"test begin"<<endl;

    string input_test = "23";
    cout<<letterCombinations(input_test).size()<<endl;

    return 0;
}