class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int res = 0, maxAge = 120;
        vector<int> ageCount(maxAge + 1, 0);
        for (int age : ages) ++ageCount[age];
        for (int A = 1; A <= maxAge; ++A) {
            for (int B = 0.5 * A + 7 + 1; B <= A; ++B)
                // must minus (A == B)
                res += ageCount[A] * (ageCount[B] - (A == B));
        }
        return res;
    }
};