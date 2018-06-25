#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<queue>

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
    stack<int> s_index;

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '(')
            s_index.push(i);
        else
        {
            if (!s_index.empty())
            {
                s_judge[i] = true;
                s_judge[s_index.top()] = true;
                s_index.pop();
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

            cursor_index = test_pointer + 1;

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

bool isValid(string s) {
    stack<char> s_store;
    if (s.length() == 0)
        return true;
        
    for (int i = 0; i <= s.length() - 1; i++){
        if (s[i] == '(' or s[i] == '[' or s[i] == '{')
            s_store.push(s[i]);
        else{
            if (s[i] == ')'){
                if (s_store.empty() == false && s_store.top() == '(')
                    s_store.pop();
                else
                    return false;
            }
            else if (s[i] == ']'){
                if (s_store.empty() == false && s_store.top() == '[')
                    s_store.pop();
                else
                    return false;
            }
            else if (s[i] == '}'){
                if (s_store.empty() == false && s_store.top() == '{')
                    s_store.pop();
                else
                    return false;
            }
            else
                return false;
        }
    }
    return s_store.empty();
}

int strStr(string haystack, string needle) {
    if (needle.length() == 0 || (haystack.length() == 0 && needle.length() == 0))
        return 0;
    else if (haystack.length() == 0 && needle.length() > 0)
        return -1;
    else{
        bool if_match = false;
        for (int i = 0; i <= haystack.length() - 1; i++){
            if (haystack[i] == needle[0]){
                for (int j = 0; j <= needle.length() - 1; j++){
                    if (needle[j] != haystack[i + j])
                        break;
                    if (j == needle.length() - 1)
                        if_match = true;
                }
                if (if_match)
                    return i;
            }
        }
        return -1;
    }
}

struct data_point{
    string word;
    int index;
};

struct cmp {
    bool operator ()(const data_point& a, const data_point& b){
        return a.index > b.index;
    }
};

vector<int> findSubstring(string s, vector<string>& words){
    vector<int> match_loc;
    if (words.size() == 0 || s.length() == 0)
        return match_loc;
    else{
        int word_len = words[0].length();
        int begin_index = 0;
        int end_index = 0;

        map<string, int> word_num;
        map<string, int> word_count;
        for (int i = 0; i <= words.size() - 1; i++){
            if (word_num.count(words[i]) == 0){
                word_num[words[i]] = 1;
                word_count[words[i]] = 0;
            }
            else
                word_num[words[i]] += 1;
        }

        priority_queue<data_point, vector<data_point>, cmp> word_index_data;

        while (begin_index <= s.length() - 1){
            end_index = begin_index;
            while (end_index <= s.length() - word_len){
                string one_test_word = s.substr(end_index, word_len);
                bool if_exist = false;
                for (int i = 0; i <= words.size() - 1; i++){
                    if (words[i] == one_test_word){
                        if_exist = true;
                        break;
                    }
                }

                // if (if_exist){
                //     if (word_count[one_test_word] < word_num[one_test_word]){
                //         struct data_point new_word_input;
                //         new_word_input.index = end_index;
                //         new_word_input.word = one_test_word;
                //         word_index_data.push(new_word_input);
                //         word_count[one_test_word]++;
                //         end_index += word_len;
                //     }
                //     else{
                //         while (word_index_data.top().word != one_test_word){
                //             word_count[word_index_data.top().word]--;
                //             word_index_data.pop();
                //         }
                //         begin_index = word_index_data.top().index + word_len;
                //         word_count[word_index_data.top().word]--;
                //         word_index_data.pop();
                //     }
                // }
                if (if_exist && (word_count[one_test_word] < word_num[one_test_word])){
                    struct data_point new_word_input;
                    new_word_input.index = end_index;
                    new_word_input.word = one_test_word;
                    word_index_data.push(new_word_input);
                    word_count[one_test_word]++;
                    end_index += word_len;
                }
                else
                    break;
            }
            bool if_all_match = true;
            for (int i = 0; i <= words.size() - 1; i++){
                if (word_count[words[i]] != word_num[words[i]]){
                    if_all_match = false;
                    break;
                }
            }

            if (if_all_match){
                match_loc.push_back(begin_index);
                while (!word_index_data.empty()){
                    word_count[word_index_data.top().word]--;
                    word_index_data.pop();
                }
                begin_index += 1;
                end_index = begin_index;
            }
            else{
                while (!word_index_data.empty()){
                    word_count[word_index_data.top().word]--;
                    word_index_data.pop();
                }
                begin_index += 1;
                end_index = begin_index;
            }
        }
    }
    return match_loc;
}

string countAndSay(int n) {
    if (n <= 0)
        return "";
    else if (n == 1)
        return "1";
    else{
        string s_prev = "1";
        int index = 1;
        n--;
        while (index <= n){
            string s_new;
            int i = 0;
            while (i < s_prev.length()){
                char current_char = s_prev[i];
                int current_char_count = 1;
                if (i < s_prev.length() - 1){
                    while (s_prev[i + 1] == s_prev[i]){
                        i++;
                        current_char_count++;
                    }
                }
                s_new += current_char_count + '0';
                s_new += current_char;
                i++;
            }
            if (index == n)
                return s_new;
            else{
                s_prev = s_new;
                index++;
            }
        }
        return "";
    }
}



int main()
{
    cout<<"test begin"<<endl;

    string test1 = "barfoothefoobarman";
    vector<string> test2;
    test2.push_back("foo");
    test2.push_back("bar");
    // test2.push_back("best");
    // test2.push_back("good");
    cout<<countAndSay(4)<<endl;

    return 0;
}