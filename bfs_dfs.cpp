#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>

using namespace std;

void generateParenthesis_bfs(vector<string> &result_get, string current_str, int remaining_left, int remaining_right){
    if (remaining_left == 0 && remaining_right == 0){
        result_get.push_back(current_str);
        return;
    }
    else{
        if (remaining_left > 0)
            generateParenthesis_bfs(result_get, current_str + '(', remaining_left - 1, remaining_right);
        if (remaining_right > 0 && remaining_right > remaining_left)
            generateParenthesis_bfs(result_get, current_str + ')', remaining_left, remaining_right - 1);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    string str_init;
    generateParenthesis_bfs(result, str_init, n, n);
    return result;
}


int main()
{
    cout<<"test begin"<<endl;

    // string input_test = "23";
    cout<<generateParenthesis(3).size()<<endl;

    return 0;
}