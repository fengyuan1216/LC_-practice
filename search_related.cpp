#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;


double findMedianSortedArrays_recur(bool if_odd, vector<int>& nums1, vector<int>& nums2, int lo1, int hi1, int left_part_size){
    int left1, left2, right1, right2;
    int lower_bound = min(nums1[0], nums2[0]);
    int upper_bound = max(nums1[nums1.size()-1], nums2[nums2.size()-1]);

    int cut1 = (lo1 + hi1) / 2 - (((lo1 + hi1) / 2) % 2);
    int cut2 = left_part_size * 2 - cut1;

    if (cut1 <= 0)
        left1 = lower_bound - 1;
    else
        left1 = nums1[cut1 / 2 - 1];
    
    if (cut1 >= 2 * nums1.size())
        right1 = upper_bound + 1;
    else
        right1 = nums1[cut1 / 2];

    if (cut2 <= 0)
        left2 = lower_bound - 1;
    else
        left2 = nums2[cut2 / 2 - 1];

    if (cut2 >= 2 * nums2.size())
        right2 = upper_bound + 1;
    else
        right2 = nums2[cut2 / 2];

    if ((left1 <= right2) && (left2 <= right1)){
        if (if_odd)
            return (double)max(left1, left2);
        else
            return ((double)max(left1, left2) + (double)min(right1, right2)) / 2.0;
    }
    else{
        if (left2 > right1)
            return findMedianSortedArrays_recur(if_odd, nums1, nums2, cut1 + 2, hi1, left_part_size);
        else
            return findMedianSortedArrays_recur(if_odd, nums1, nums2, lo1, cut1 - 2, left_part_size);
    }
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > 0 && nums2.size() > 0){
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);
        
        int total_len = nums1.size() + nums2.size();
        int left_part_size = 0;
        if (total_len % 2)
            left_part_size = (total_len + 1) / 2;
        else
            left_part_size = total_len / 2;

        return findMedianSortedArrays_recur(total_len % 2, nums1, nums2, 0, 2 * nums1.size(), left_part_size);
    }
    else{
        if (nums1.size() == 0){
            if (nums2.size() % 2)
                return (double)nums2[nums2.size() / 2];
            else
                return ((double)nums2[nums2.size() / 2] + (double)nums2[nums2.size() / 2 - 1]) / 2.0;
        }
        else
            return findMedianSortedArrays(nums2, nums1);
    }
}

int search(vector<int>& nums, int target) {
    if (nums.size() == 0)
        return -1;

    int lo = 0;
    int hi = nums.size() - 1;
    int mid = (lo + hi) / 2;
    
    if (nums[0] > nums[nums.size() - 1]){
        while (hi - lo > 1){
            mid = (lo + hi) / 2;
            if (nums[mid] > nums[lo])
                lo = mid;
            if (nums[mid] < nums[hi])
                hi = mid;
        }
        if (target <= nums[nums.size() - 1]){
            lo = hi;
            hi = nums.size() - 1;
        }
        else{
            hi = lo;
            lo = 0;
        }
    }

    while (lo <= hi){
        mid = (lo + hi) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}

vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> range;
    if (nums.size() == 0){
        range.push_back(-1);
        range.push_back(-1);
        return range;
    }
        
    int lo = 0;
    int hi = nums.size() - 1;
    int mid;
    bool if_find = false;

    while (lo <= hi){
        mid = (lo + hi) / 2;
        if (nums[mid] == target){
            if_find = true;
            break;
        }
        else if (nums[mid] > target)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    if (if_find == false){
        range.push_back(-1);
        range.push_back(-1);
        return range;
    }
    else{
        int mid_index = mid;

        lo = 0;
        hi = mid_index;
        double left_ref = target - 0.5;
        if (nums[lo] == target)
            range.push_back(lo);
        else{
            while (hi - lo > 1){
                mid = (lo + hi) / 2;
                if (nums[mid] > left_ref)
                    hi = mid;
                if (nums[mid] < left_ref)
                    lo = mid;
            }
            range.push_back(hi);
        }
        
        lo = mid_index;
        hi = nums.size() - 1;
        double right_ref = target + 0.5;
        if (nums[hi] == target)
            range.push_back(hi);
        else{
            while (hi - lo > 1){
                mid = (lo + hi) / 2;
                if (nums[mid] < right_ref)
                    lo = mid;
                if (nums[mid] > right_ref)
                    hi = mid;
            }
            range.push_back(lo);
        }

        return range;
    }
}

int searchInsert(vector<int>& nums, int target) {
    if (nums.size() == 0)
        return 0;

    int lo = 0;
    int hi = nums.size() - 1;
    int mid;

    while (lo <= hi){
        mid = (lo + hi) / 2;
        if (nums[mid] == target)
            return mid;
        else{
            if (lo == hi)
                break;
            if (nums[mid] < target)
                lo = mid + 1;
            if (nums[mid] > target)
                hi = mid - 1;
        }
    }

    if (nums[lo] < target)
        return lo + 1;
    else
        return lo;
}


int main()
{
    vector<int> s1;
    s1.push_back(4);
    // s1.push_back(5);
    // s1.push_back(1);
    // s1.push_back(2);
    // s1.push_back(3);
    

    cout<<"test"<<endl;

    cout<<search(s1, 4)<<endl;

    return 0;
}