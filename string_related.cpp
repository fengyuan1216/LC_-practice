#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;



string longestPalindrome(string s)
{
    string s_expand;
    for (int i = 0; i < s.length(); ++i)
    {
        s_expand += '#';
        s_expand += s[i];
    }
    s_expand += '#';

    vector<int> s_dis(2 * s.length() + 1, 1);
    
    int max_right = 0;
    int max_center = 0;

    for (int i = 0; i < s_dis.size(); ++i)
    {
        if (i <= max_right)
            s_dis[i] = min(s_dis[2 * max_center - max_right], max_right - i + 1);

        while ((i + s_dis[i] < s_dis.size()) && (i - s_dis[i] >= 0))
        {
            if (s_expand[i + s_dis[i]] == s_expand[i - s_dis[i]])
                s_dis[i]++;
            else
                break;
        }

        if (s_dis[i] > s_dis[max_center])
        {
            max_center = i;
            max_right = i + s_dis[i] - 1;
        }
    }

    string longest_p;
    for (int i = max_center - s_dis[max_center] + 1; i <= max_center + s_dis[max_center] - 1; ++i)
    {
        if (s_expand[i] != '#')
            longest_p += s_expand[i];
    }

    return longest_p;
}

int longestValidParentheses(string s)
{
    vector<bool> s_judge(s.length(), false);
    stack<char> s_symbol;
    stack<int> s_index;

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '(')
        {
            s_symbol.push('(');
            s_index.push(i);
        }
        else
        {
            if ((!s_symbol.empty()) && (s_symbol.top() == '('))
            {
                s_judge[i] = true;
                s_judge[s_index.top()] = true;
                s_symbol.pop();
                s_index.pop();
            }
            else
            {
                s_symbol.push(')');
                s_index.push(i);
            }
        }
    }

    int longest_len = 0;
    int cursor_index = 0;

    while (cursor_index <= s.length())
    {
        if (s_judge[cursor_index])
        {
            int current_len = 0;
            int test_pointer = cursor_index;

            while (test_pointer < s.length() && s_judge[test_pointer])
            {
                test_pointer++;
                current_len++;
            }

            cursor_index = test_pointer;

            if (current_len > longest_len)
                longest_len = current_len;
        }
        else
            cursor_index++;
    }

    return longest_len;
}

int lengthOfLongestSubstring(string s)
{
    int max_len = 0;
    map<char, int> sub_s;

    int current_index = 0;
    int current_len = 0;

    while (current_index < s.length())
    {
        char current_char = s[current_index];
       
        if (sub_s.count(current_char) > 0)
        {
            int remove_duplicate_count = 0;
            int duplicate_char_index = sub_s[current_char];
            map<char, int>::iterator iter;

            for (iter = sub_s.begin(); iter != sub_s.end();)
            {
                if (iter->second <= duplicate_char_index)
                {
                    sub_s.erase(iter++);
                    remove_duplicate_count++;
                }
                else
                    iter++;
            }
            current_len -= remove_duplicate_count;
        }

        sub_s[current_char] = current_index;
        current_len++;
        current_index++;

        if (current_len > max_len)
            max_len = current_len;
    }

    return max_len;
}

string convert(string s, int numRows) {
    if ((numRows == 1) || (s.length() <= 1))
        return s;
    else if (numRows == 2){
        string s_convert;
        for (int i = 0; i < s.length(); i = i + 2)
            s_convert += s[i];
        for (int i = 1; i < s.length(); i = i + 2)
            s_convert += s[i];
        return s_convert;
    }
    else{
        string s_convert;
        int current_index = 0;
        int tuple_sum = 0;

        for (int i = 0; i < numRows; i++){
            if ((i == 0) || (i == numRows - 1)){
                for (int j = 0; ; j++){
                    if (i == 0)
                        current_index = (2 * j) * (numRows - 1);
                    else
                        current_index = (2 * j + 1) * (numRows - 1);

                    if (current_index < s.length())
                        s_convert += s[current_index];
                    else
                        break;
                }
            }
            else{
                for (int j = 0; ; j++){
                    if (j % 2){
                        tuple_sum = (4 * numRows - 4) * ((j + 1) / 2);
                        current_index = tuple_sum - ((numRows - 1) * (j + 1) + i);
                    }
                    else
                        current_index = (numRows - 1) * j + i;
                    
                    if (current_index < s.length())
                        s_convert += s[current_index];
                    else
                        break;
                }
            }
        }
        return s_convert;
    }
}


bool judge_match(string s, string p, int s_index, int p_index){
    if (s_index == s.length() && p_index == p.length())
        return true;
    else{
        if ((p_index <= p.length() - 2) && (p[p_index + 1] == '*')){
            if (p[p_index] == '.'){
                while (s_index <= s.length()){
                    if (judge_match(s, p, s_index, p_index + 2))
                        return true;
                    else
                        s_index++;
                }
                return false;
            }
            else{
                if (s[s_index] != p[p_index])
                    return judge_match(s, p, s_index, p_index + 2);
                else{
                    int max_right_index = s_index;
                    while (max_right_index <= s.length() - 2 && s[max_right_index + 1] == s[s_index])
                        max_right_index++;

                    for (int s_index_cursor = s_index; s_index_cursor <= max_right_index + 1; s_index_cursor++){
                        if (judge_match(s, p, s_index_cursor, p_index + 2))
                            return true;
                    }
                    return false;
                }
            }
        }
        else if (p[p_index] == '.')
            return judge_match(s, p, s_index + 1, p_index + 1);
        else{
            if (s[s_index] == p[p_index])
                return judge_match(s, p, s_index + 1, p_index + 1);
            else
                return false;
        }
    }
}

bool isMatch(string s, string p) {
    if (s.length() == 0 && p.length() == 0)
        return true;
    else if (s.length() != 0 && p.length() == 0)
        return false;
    else
        return judge_match(s, p, 0, 0);
}

string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 0)
        return "";
    else{
        string common_prefix = "";
        int str_index = 0;
        bool if_end = false;

        while (!if_end){
            for (int i = 0; i < strs.size(); i++){
                if (str_index >= strs[i].size()){
                    if_end = true;
                    break;
                }
            }

            if (!if_end){
                char single_common = strs[0][str_index];
                if (strs.size() > 1){
                    bool if_same = true;
                    for (int j = 1; j < strs.size(); j++){
                        if (strs[j][str_index] != single_common)
                            if_same = false;
                    }
                    if (if_same)
                        common_prefix += single_common;
                    else
                        break;
                }
                else
                    common_prefix += single_common;

                str_index++;
            }
        }
        return common_prefix;
    }
}


int main()
{
    cout<<"test begin"<<endl;

    vector<string> test_vector;
    test_vector.push_back("aca");
    test_vector.push_back("cba");
    cout<<longestCommonPrefix(test_vector)<<endl;

    return 0;
}