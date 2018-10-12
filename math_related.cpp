#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;

int reverse(int x){
    if (x == (1<<31) || x == 0)
        return 0;
    else{
        int x_sign = 1;
        if (x < 0){
            x = -x;
            x_sign = -1;
        }
        
        stack<int> number_store;
        while (x){
            number_store.push(x % 10);
            x /= 10;
        }

        while (number_store.top() == 0)
            number_store.pop();
        
        long int x_reverse = 0;
        long int power_num = 1;
        while (!number_store.empty()){
            x_reverse += number_store.top() * power_num;
            number_store.pop();
            power_num *= 10;
        }

        long int max_compare = ~ (1 << 31);
        if (x_reverse > max_compare)
            return 0;
        else{
            x_reverse *= x_sign;
            return x_reverse;
        }
    }
}

int myAtoi(string str) {
    int str_index = 0;
    while ((str_index < str.length()) && (str[str_index] == ' '))
        str_index++;
    
    bool if_negative = false;
    if (str_index < str.length()){
        if (str[str_index] == '-'){
            if_negative = true;
            str_index++;
        }
        else{
            if (str[str_index] == '+'){
                if_negative = false;
                str_index++;
            }   
        }
    }
    
    while ((str_index < str.length()) && (str[str_index] == '0'))
        str_index++;

    if (str_index >= str.length())
        return 0;
    else{
        if (str[str_index] > '9' || str[str_index] < '0')
            return 0;
        else{
            stack<int> str_number;

            while (str_index < str.length()){
                if (str[str_index] <= '9' && str[str_index] >= '0'){
                    str_number.push(int(str[str_index]) - int('0'));
                    str_index++;
                }
                else
                    break;
            }
            
            long int max_compare = ~(1 << 31);
            long int min_compare = 1 << 31;
            long int pow_base = 1;
            long int number_retract = 0;

            while (!str_number.empty()){
                if (if_negative)
                    number_retract -= str_number.top() * pow_base;
                else
                    number_retract += str_number.top() * pow_base;

                str_number.pop();

                if ((if_negative == false) && ((number_retract > max_compare) || (pow_base > max_compare))) 
                    return (int)max_compare;
                if ((if_negative == true) && ((number_retract < min_compare) || (pow_base > max_compare)))
                    return (int)min_compare;
                
                pow_base *= 10;
            }

            return (int)number_retract;
        }
    }
}

bool isPalindrome(int x) {
    if (x < 0)
        return false;
    else{
        int compare_left = 1;
        int compare_right = 1;

        while (x / compare_left >= 10)
            compare_left *= 10;
        
        while (compare_left >= compare_right){
            if (((x / compare_left) % 10) == ((x / compare_right) % 10)){
                compare_left /= 10;
                compare_right *= 10;
            }
            else
                return false;
        }
        return true;
    }
}

int maxArea(vector<int>& height) {
    int left_index = 0;
    int right_index = height.size() - 1;
    int max_area = 0;

    while (left_index < right_index){
        max_area = max(max_area, min(height[left_index], height[right_index]) * (right_index - left_index));
        if (height[left_index] > height[right_index])
            right_index--;
        else
            left_index++;
    }

    return max_area;
}

string intToRoman(int num) {
    map<int, string> base_relation;

    base_relation[1] = "I";
    base_relation[5] = "V";
    base_relation[10] = "X";
    base_relation[50] = "L";
    base_relation[100] = "C";
    base_relation[500] = "D";
    base_relation[1000] = "M";

    base_relation[4] = "IV";
    base_relation[9] = "IX";
    base_relation[40] = "XL";
    base_relation[90] = "XC";
    base_relation[400] = "CD";
    base_relation[900] = "CM";

    vector<int> base_int;
    base_int.push_back(1000);
    base_int.push_back(900);
    base_int.push_back(500);
    base_int.push_back(400);
    base_int.push_back(100);
    base_int.push_back(90);
    base_int.push_back(50);
    base_int.push_back(40);
    base_int.push_back(10);
    base_int.push_back(9);
    base_int.push_back(5);
    base_int.push_back(4);
    base_int.push_back(1);

    string num_roman = "";
    int base_index = 0;

    while (num > 0){
        if (num >= base_int[base_index]){
            num -= base_int[base_index];
            num_roman += base_relation[base_int[base_index]];
        }
        else
            base_index++;
    }

    return num_roman;
}

int romanToInt(string s) {
    int num_int = 0;
    int s_index = 0;
    map<char, int> base_relation;

    base_relation['I'] = 1;
    base_relation['V'] = 5;
    base_relation['X'] = 10;
    base_relation['L'] = 50;
    base_relation['C'] = 100;
    base_relation['D'] = 500;
    base_relation['M'] = 1000;

    while (s_index < s.length()){
        if (s[s_index] == 'V' || s[s_index] == 'L' ||s [s_index] == 'D' || s[s_index] == 'M'){
            num_int += base_relation[s[s_index]];
            s_index++;
        }
        if (s[s_index] == 'I'){
            if (s_index < s.length() - 1 && s[s_index + 1] == 'V'){
                num_int += 4;
                s_index = s_index + 2;
            }
            else if (s_index < s.length() - 1 && s[s_index + 1] == 'X'){
                num_int += 9;
                s_index = s_index + 2;
            }
            else{
                num_int += 1;
                s_index++;
            }
        }
        if (s[s_index] == 'X'){
            if (s_index < s.length() - 1 && s[s_index + 1] == 'L'){
                num_int += 40;
                s_index = s_index + 2;
            }
            else if (s_index < s.length() - 1 && s[s_index + 1] == 'C'){
                num_int += 90;
                s_index = s_index + 2;
            }
            else{
                num_int += 10;
                s_index++;
            }
        }
        if (s[s_index] == 'C'){
            if (s_index < s.length() - 1 && s[s_index + 1] == 'D'){
                num_int += 400;
                s_index = s_index + 2;
            }
            else if (s_index < s.length() - 1 && s[s_index + 1] == 'M'){
                num_int += 900;
                s_index = s_index + 2;
            }
            else{
                num_int += 100;
                s_index++;
            }
        }
    }

    return num_int;
}

int divide(int dividend, int divisor) {
    int max_int = ~ (1 << 31);
    int min_int = 1 << 31;

    if (dividend == min_int && divisor == -1)
        return max_int;
    else{
        long int dividend_expand = dividend;
        long int divisor_expand = divisor;
        bool if_same_sign = true;
        if (dividend_expand < 0){
            dividend_expand = -dividend_expand;
            if_same_sign = !if_same_sign;
        }
        if (divisor_expand < 0){
            divisor_expand = -divisor_expand;
            if_same_sign = !if_same_sign;
        }

        vector<long int> divisor_expand_table;
        vector<long int> value_expand_table;
        long int divisor_tmp = divisor_expand;
        long int value_tmp = 1;
        while (divisor_tmp <= dividend_expand){
            divisor_expand_table.push_back(divisor_tmp);
            value_expand_table.push_back(value_tmp);
            divisor_tmp = divisor_tmp << 1;
            value_tmp = value_tmp << 1;
        }

        long int counter = 0;
        for (int index = divisor_expand_table.size() - 1; index >= 0; index--){
            while (dividend_expand >= divisor_expand_table[index]){
                dividend_expand -= divisor_expand_table[index];
                counter += value_expand_table[index];
            }
        }

        int return_val = 0;
        if (if_same_sign)
            return_val = counter;
        else
            return_val = -counter;
        return return_val;
    }
}

int trap(vector<int>& height) {
    if (height.size() == 0 || height.size() == 1){
        return 0;
    }

    int current_max_height = height[0];

    int trap_left = 0;
    for (int i = 0; i < height.size(); i++) {
        trap_left += current_max_height - height[i];
        if (i + 1 < height.size() && height[i + 1] > current_max_height) {
            current_max_height = height[i + 1];
        }
    }

    current_max_height = height[height.size() - 1];
    int trap_right = 0;
    for (int i = height.size() - 1; i >= 0; i--) {
        trap_right += current_max_height - height[i];
        if (i - 1 >= 0 && height[i - 1] > current_max_height) {
            current_max_height = height[i - 1];
        }
    }

    int trap_all = 0;
    for (int i = 0; i < height.size(); i++) {
        trap_all += current_max_height - height[i];
    }

    return trap_left + trap_right - trap_all;
}

int jump(vector<int>& nums) {
    if (nums.size() <= 1) {
        return 0;
    }

    int step = 0;
    int current_index = 0;

    while (current_index < nums.size() - 1) {
        int far_index = 0;
        int new_current_index = current_index;
        
        for (int tmp_move = 1; tmp_move <= nums[current_index]; tmp_move++) {
            if (tmp_move + current_index < nums.size() - 1) {
                if (tmp_move + nums[tmp_move + current_index] > far_index) {
                    far_index = tmp_move + nums[tmp_move + current_index];
                    new_current_index = current_index + tmp_move;
                }
            }
            else {
                return step + 1;
            }
        }

        current_index = new_current_index;
        step++;
    }

    return step;
}

void rotate(vector<vector<int> >& matrix) {
    if (matrix.size() == 0) {
        return;
    }
    int m = matrix.size();
    int n = matrix[0].size();
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}


int main()
{
    cout<<"test begin"<<endl;

    vector<int> s1;
    s1.push_back(2);
    s1.push_back(3);
    s1.push_back(1);
    // s1.push_back(1);
    // s1.push_back(4);

    cout<<jump(s1)<<endl;

    return 0;
}