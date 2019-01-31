#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>

using namespace std;


vector<int> solution(int D, vector<int> A) {
    int n = A.size();
    vector<int> ans;

    if (n == 0) {
        return ans;
    }

    for (int i = 0; i < n; i++) {
        int cnt = 0;
        int node = A[i];

        while (cnt < D-1 && node != -1) {
            cnt++;
            node = A[node];
        }

        if (cnt == D-1) {
            ans.push_back(node);
        }
        else {
            ans.push_back(-1);
        }
    }
    return ans;
}


int main() {

    int tmp[] = {-1, 0, 4, 2, 1};
    int sizetmp = sizeof(tmp) / sizeof(int);
    vector<int> A(tmp, tmp+sizetmp);
    int D = 3;

    vector<int> ans = solution(D, A);

    for (int i = 0; i < ans.size(); i++)
        cout<<ans[i]<<",";
    cout<<endl;


    return 0;
}