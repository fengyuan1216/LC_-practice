#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>

using namespace std;


void dfs(map<char, vector<char>>& p_to_son, string& ans, char cur_ch) {
    if (p_to_son.find(cur_ch) == p_to_son.end()) {
        ans += cur_ch;
        return;
    }

    ans += cur_ch;
    ans += '(';
    for (int i = 0; i < p_to_son[cur_ch].size(); i++) {
        dfs(p_to_son, ans, p_to_son[cur_ch][i]);
        ans += ')';
    }
    return;
}


int main() {

    int p_index = 1;

    if (p_index == 0) {

        int t_num = 0;
        cin >> t_num;

        int tmp = 0;

        vector<vector<int> > data(t_num, vector<int>(0));
        for (int i = 0; i < t_num; i++) {
            cin >> tmp;
            data[i].push_back(tmp);
            while (cin.get() != '\n') {
                cin >> tmp;
                data[i].push_back(tmp);
            }
        }

        for (int i = 0; i < t_num; i++) {
            for (int j = 0; j < data[i].size(); j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < t_num; i++) {
            int sum = 0;
            int cur_max = INT_MIN;
            for (int j = data[i].size() - 1; j >= 0; j--) {
                cur_max = max(cur_max, data[i][j]);
                sum += cur_max - data[i][j];
            }
            cout << sum << endl;
        }
    }

    //////////////////////////


    if (p_index == 1) {
        char input_charlist[] = "(B,D) (D,E) (A,C) (C,F) (E,G) (A,B)";
        string input_str(input_charlist);
//        string input_str = "(B,D) (D,E) (A,C) (C,F) (E,G) (A,B)";
//        string input_str = "(A,B) (A,C) (C,D) (D,A)";

        bool err_more_son = false;
        bool err_cycle = false;
        bool err_dup_edge = false;
        bool err_multi_root = false;

        vector<vector<char> > data;
        vector<char> one_data;

        map<char, vector<char>> p_to_son;
        unordered_map<char, char> s_to_root;
        unordered_map<char, char> dup_check;

        int start_index = 0;
        char tmp1;
        char tmp2;
        while (start_index < input_str.length()) {
            start_index = input_str.find('(', start_index);
            if (start_index == -1) {
                break;
            }

            tmp1 = input_str.substr(start_index, 5)[1];
            tmp2 = input_str.substr(start_index, 5)[3];

            //////////////////
            if (dup_check.find(tmp1) != dup_check.end()) {
                char find_ch = dup_check[tmp1];
                if (find_ch == tmp2)
                    err_dup_edge = true;
            }
            else
                dup_check[tmp1] = tmp2;

            //////////////////
            if (p_to_son.find(tmp1) != p_to_son.end()) {
                p_to_son[tmp1].push_back(tmp2);
            }
            else {
                vector<char> one_data_p;
                one_data_p.push_back(tmp2);
                p_to_son[tmp1] = one_data_p;
            }

            s_to_root[tmp2] = tmp1;
            start_index++;
        }

        unordered_map<char, char>::iterator it;
        for (it = s_to_root.begin(); it != s_to_root.end(); it++) {
            char pre = it->second;
            char post = it->first;
            while (true) {
                if (s_to_root.find(pre) == s_to_root.end() || pre == post)
                    break;
                else {
                    if (pre == s_to_root[pre])
                        break;
                    else
                        pre = s_to_root[pre];
                }

            }
            s_to_root[post] = pre;
        }

        /////////////////////////////////////////
        map<char, vector<char>>::iterator it1a;
        for (it1a = p_to_son.begin(); it1a != p_to_son.end(); it1a++) {
            if (it1a->second.size() > 2) {
                err_more_son = true;
                break;
            }
        }

        unordered_map<char, char>::iterator it2a;
        char root_ch = '1';
        for (it2a = s_to_root.begin(); it2a != s_to_root.end(); it2a++) {
            if (root_ch == '1')
                root_ch = it2a->second;
            else {
                if (root_ch != it2a->second)
                    err_multi_root = true;
            }

            if (it2a->first == it2a->second)
                err_cycle = true;
        }

        if (err_cycle || err_dup_edge || err_more_son || err_multi_root)
            return 0;

        /////////////////////////////////////////

        for (it1a = p_to_son.begin(); it1a != p_to_son.end(); it1a++) {
            sort(it1a->second.begin(), it1a->second.end());
        }

        /////////////////////////////////////////

        string ans = "";
        dfs(p_to_son, ans, root_ch);
        cout<<ans<<endl;


//        /////////////////////////////////////////
        map<char, vector<char>>::iterator it1;
        for (it1 = p_to_son.begin(); it1 != p_to_son.end(); it1++) {
            cout<<it1->first<<" - ";
            for (int i = 0; i < it1->second.size(); i++) {
                if (i < it1->second.size() - 1)
                    cout<<it1->second[i]<<", ";
                else
                    cout<<it1->second[i]<<endl;
            }
        }

        cout<<endl;

        unordered_map<char, char>::iterator it2;
        for (it2 = s_to_root.begin(); it2 != s_to_root.end(); it2++) {
            cout<<it2->first<<", "<<it2->second<<endl;
        }


    }
[-1,8,6,0,7,3,8,9,-1,6]

    //////////////////////////

//    string test = "123";
//    int x = stoi(test);
//    cout<<x<<endl;
//
//    int y = 456;
//    string test2 = to_string(y);
//    cout<<test2<<", "<<test2.length()<<endl;
//
//    int len = 3;
//    string* ps = new string[len];
//    ps[0] = "aa";
//    ps[1] = "bb";
//    ps[2] = "cc";
//    cout<<*ps<<endl;
//    cout<<*(ps+1)<<endl;
//    cout<<*(ps+2)<<endl;


    char s[5000];
    int p, i, Half, Left, Right, Count;
    while(cin>>s)
    {
        i = strlen(s);  
        Count = 0;

        for(p=0; p<=i-1; p++)  
        {  
            Half = ((i-1)-p) / 2;  
            //如果子串是奇数个  
            if( ((i-1)-p)%2 == 0 )  
            {  
                Left = p + Half - 1;  
                Right = p + Half + 1;  
            }  
            else   //如果子串是偶数个  
            {  
                Left = p + Half;  
                Right = p + Half + 1;  
            }  
            while( Left >= p )  
            {  
                if( s[Left] == s[Right])    
                {  
                        Count++;  
                        Left--;  
                        Right++;  
                    }  
                else
                {  
                    break;  
                }  
                }  
            }  
            for(p=i-2; p>=1; p--)  
            {  
                Half = p / 2;  
                //如果子串是奇数个  
                if( p%2 == 0 )  
                {  
                    Left = Half - 1;  
                    Right = Half + 1;  
                }  
                else   //如果子串是偶数个  
                {  
                    Left = Half;  
                    Right = Half + 1;  
                }  
                while( Left >= 0 )  
                {  
                    if( s[Left] == s[Right] )  
                {  
                        Count++;  //发现了一个回文串  
                        Left--;  
                        Right++;  
                    }  
                    else  //如果不相等，立即终止，由中心向外扩散不可能会有回文串  
                    {  
                        break;  
                    }  
                }  
            }  
        printf("%d\n",Count + i);  
    }  


    return 0;
}