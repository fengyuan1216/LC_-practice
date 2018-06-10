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

    vector<int> base_int = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

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


int main()
{
    cout<<"test begin"<<endl;

    cout<<isPalindrome(1221)<<endl;
    // cout<<(1<<31);

    return 0;
}