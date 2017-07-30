class Solution(object):
    def hammingDistance(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        xor = x ^ y
        ans = 0
        while xor != 0:
            print(bin(xor))
            if xor & 1 == 1:
                ans += 1
            xor = xor >> 1
        return ans