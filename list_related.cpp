#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>

using namespace std;


 struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == NULL)
        return head;
    else{
        ListNode* p_right = head;
        ListNode* p_left = head;
        for (int i = 0; i <= n - 1; i++){
            if (p_right == NULL)
                return NULL;
            else
                p_right = p_right->next;
        }

        if (p_right == NULL)
            return head->next;

        while (p_right->next != NULL){
            p_left = p_left->next;
            p_right = p_right->next;
        }

        p_left->next = p_left->next->next;
        return head;
    }
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode tmp_head_node(-1);
    ListNode* cursor = &tmp_head_node;
    while (l1 && l2){
        if (l1->val <= l2->val){
            cursor->next = l1;
            l1 = l1->next;
        }
        else{
            cursor->next = l2;
            l2 = l2->next;
        }
        cursor = cursor->next;
    }
    if (l1)
        cursor->next = l1;
    if (l2)
        cursor->next = l2;
    return tmp_head_node.next;
}


int main()
{
    return 0;
}