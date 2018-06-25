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

bool isValidSudoku(vector<vector<char>>& board) {
    int line_judge[9][9];
    int col_judge[9][9];
    int block_judge[9][9];
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            line_judge[i][j] = 0;
            col_judge[i][j] = 0;
            block_judge[i][j] = 0;
        }
    }

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (board[i][j] != '.'){
                if (line_judge[i][board[i][j] - '1'] > 0)
                    return false;
                else
                    line_judge[i][board[i][j] - '1'] = 1;
            }
        }
    }

    for (int j = 0; j < 9; j++){
        for (int i = 0; i < 9; i++){
            if (board[i][j] != '.'){
                if (col_judge[j][board[i][j] - '1'] > 0)
                    return false;
                else
                    col_judge[j][board[i][j] - '1'] = 1;
            }
        }
    }

    for (int block_i = 0; block_i < 3; block_i++){
        for (int block_j = 0; block_j < 3; block_j++){
            int block_index = 3 * block_i + block_j;
            for (int i = block_i * 3; i < block_i * 3 + 3; i++){
                for (int j = block_j * 3; j < block_j * 3 + 3; j++){
                    if (board[i][j] != '.'){
                        if (block_judge[block_index][board[i][j] - '1'] > 0)
                            return false;
                        else
                            block_judge[block_index][board[i][j] - '1'] = 1;
                    }
                }
            }
        }
    }

    return true;
}

bool solveSudoku_check_valid(vector<vector<char>>& board, int line_index, int col_index, char check_char){
    for (int j = 0; j < 9; j++){
        if (board[line_index][j] == check_char)
            return false;
    }
    for (int i = 0; i < 9; i++){
        if (board[i][col_index] == check_char)
            return false;
    }
    int block_i = line_index / 3;
    int block_j = col_index / 3;
    for (int i = block_i * 3; i < block_i * 3 + 3; i++){
        for (int j = block_j * 3; j < block_j * 3 + 3; j++){
            if (board[i][j] == check_char)
                return false;
        }
    }
    return true;
}

bool solveSudoku_recur(vector<vector<char>>& board, vector<pair<int, int> >& fill_form, int current_progress){
    if (current_progress == fill_form.size())
        return true;
    else{
        int line_index = fill_form[current_progress].first;
        int col_index = fill_form[current_progress].second;
        for (char test_char = '1'; test_char <= '9'; test_char++){
            if (solveSudoku_check_valid(board, line_index, col_index, test_char)){
                board[line_index][col_index] = test_char;
                if (solveSudoku_recur(board, fill_form, current_progress + 1))
                    return true;
                board[line_index][col_index] = '.';
            }
        }
        return false;
    }
}

void solveSudoku(vector<vector<char>>& board) {
    vector<pair<int, int> > fill_form_all;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (board[i][j] == '.'){
                fill_form_all.push_back(make_pair(i, j));
            }
        }
    }
    solveSudoku_recur(board, fill_form_all, 0);
}

int main()
{
    cout<<"test begin"<<endl;

    // string input_test = "23";
    cout<<generateParenthesis(3).size()<<endl;

    return 0;
}