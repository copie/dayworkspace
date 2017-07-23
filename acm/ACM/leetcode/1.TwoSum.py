class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        tmp=[]
        for i in range(0,len(nums)):
                if target - nums in tmp:
                    return (tmp[target-nums[i]]+1,i+1)
                else:
                    tmp[nums[i]]=i
        else:
            return -1,-1