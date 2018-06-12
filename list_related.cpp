#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#include<queue>

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

struct data_point {
    int value;
    int index;
};

struct cmp {
    bool operator ()(const data_point& a, const data_point& b){
        return a.value > b.value;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() == 0)
        return NULL;

    priority_queue<data_point, vector<data_point>, cmp> front_data;
    ListNode tmp_head_node(-1);
    ListNode* new_cursor = &tmp_head_node;

    vector<ListNode*> p_cursor;
    for (int i = 0; i <= lists.size() - 1; i++){
        p_cursor.push_back(lists[i]);
        if (lists[i]){
            struct data_point one_node;
            one_node.value = lists[i] -> val;
            one_node.index = i;
            front_data.push(one_node);
        }
    }

    while (true){
        if (front_data.size() == 0)
            break;
        else{
            int min_value_index = front_data.top().index;
            new_cursor -> next = p_cursor[min_value_index];
            new_cursor = new_cursor -> next;

            p_cursor[min_value_index] = p_cursor[min_value_index] -> next;
            front_data.pop();

            if (p_cursor[min_value_index] != NULL){
                struct data_point one_node;
                one_node.value = p_cursor[min_value_index] -> val;
                one_node.index = min_value_index;
                front_data.push(one_node);
            }
        }
    }

    return tmp_head_node.next;
}

ListNode* swapPairs(ListNode* head) {
    if (head == NULL)
        return NULL;
    else{
        ListNode* next_head = head -> next;
        if (next_head != NULL)
            next_head = next_head -> next;
        else
            return head;
        
        ListNode* new_head = head -> next;
        new_head -> next = head;
        head -> next = swapPairs(next_head);
        return new_head;
    }
}

ListNode* reverseKGroup_recur(ListNode* head, int k){
    if (head == NULL)
        return NULL;
    else{
        int remaining_len = 0;
        ListNode* new_head = NULL;
        ListNode* p_tmp = head;

        while (p_tmp){
            remaining_len++;
            p_tmp = p_tmp -> next;
            if (remaining_len == k){
                new_head = p_tmp;
                break;
            }
            if (remaining_len > k)
                break;
        }
        
        if (remaining_len < k)
            return head;
        else{
            ListNode* p_cursor_right = head -> next;
            ListNode* p_cursor_left = head;
            int move_count = 0;

            while (move_count <= k - 2){
                p_tmp = p_cursor_right -> next;
                p_cursor_right -> next = p_cursor_left;
                p_cursor_left = p_cursor_right;
                p_cursor_right = p_tmp;
                move_count++;
            }
            head -> next = reverseKGroup_recur(new_head, k);
            return p_cursor_left;
        }
    }
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == NULL)
        return NULL;
    else if (k == 1)
        return head;
    else
        return reverseKGroup_recur(head, k);
}


int main()
{
    return 0;
}