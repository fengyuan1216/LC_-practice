#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>

using namespace std;

vector<vector<int> > threeSum(vector<int>& nums) {
    vector<vector<int> > result;
    sort(nums.begin(), nums.end());

    if (nums.size() < 3)
        return result;
    else{
        for (int first_index = 0; first_index <= nums.size() - 3; first_index++){
            int left = first_index + 1;
            int right = nums.size() - 1;
            while (left < right){
                int one_sum = nums[first_index] + nums[left] + nums[right];
                if (one_sum > 0)
                    right--;
                else if (one_sum < 0)
                    left++;
                else{
                    vector<int> one_result;
                    one_result.push_back(nums[first_index]);
                    one_result.push_back(nums[left]);
                    one_result.push_back(nums[right]);
                    result.push_back(one_result);
                    
                    while (left < right && left <= nums.size() - 2 && nums[left] == nums[left + 1])
                        left++;
                    left++;
                    while (right > left && right >= first_index + 2 && nums[right] == nums[right - 1])
                        right--;
                    right--;
                }
                while (nums[first_index] == nums[first_index + 1] && first_index <= nums.size() - 3)
                    first_index++;
            }
        }
        return result;
    }
}

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int result_int = 0;
    int result_gap = ~ (1 << 31);
    for (int first_index = 0; first_index < nums.size(); first_index++){
        int left = first_index + 1;
        int right = nums.size() - 1;
        while (left < right){
            int one_sum = nums[first_index] + nums[left] + nums[right];
            
            if (abs(target - one_sum) <= result_gap){
                result_gap = abs(target - one_sum);
                result_int = one_sum;
            }

            if (one_sum > target)
                right--;
            else if (one_sum < target)
                left++;
            else
                break;
        }
    }
    return result_int;
}

vector<vector<int> > fourSum(vector<int>& nums, int target) {
    vector<vector<int> > result_set;
    sort(nums.begin(), nums.end());

    if (nums.size() < 4)
        return result_set;
    else{
        for (int index_1 = 0; index_1 <= nums.size() - 4; index_1++){
            for (int index_2 = index_1 + 1; index_2 <= nums.size() - 3; index_2++){
                int current_target = target - nums[index_1] - nums[index_2];
                int left = index_2 + 1;
                int right = nums.size() - 1;

                while (left < right && left >= index_2 + 1 && right <= nums.size() - 1){
                    if (nums[left] + nums[right] > current_target)
                        right--;
                    else if (nums[left] + nums[right] < current_target)
                        left++;
                    else{
                        vector<int> one_result;
                        one_result.push_back(nums[index_1]);
                        one_result.push_back(nums[index_2]);
                        one_result.push_back(nums[left]);
                        one_result.push_back(nums[right]);
                        result_set.push_back(one_result);

                        while (right >= index_2 + 2 && nums[right - 1] == nums[right])
                            right--;
                        right--;
                        while (left <= nums.size() - 2 && nums[left + 1] == nums[left])
                            left++;
                        left++;
                    }
                }
                while (index_2 <= nums.size() - 2 && nums[index_2 + 1] == nums[index_2])
                    index_2++;
            }
            while (index_1 <= nums.size() - 2 && nums[index_1 + 1] == nums[index_1])
                index_1++;
        }
        return result_set;
    }
}


int main()
{
    cout<<"test begin"<<endl;

    vector<int> test_vector;
    test_vector.push_back(1);
    test_vector.push_back(0);
    test_vector.push_back(-1);
    test_vector.push_back(0);
    test_vector.push_back(-2);
    test_vector.push_back(2);

    vector<vector<int> > result_get = fourSum(test_vector, 0);
    cout<<result_get.size()<<endl;

    return 0;
}