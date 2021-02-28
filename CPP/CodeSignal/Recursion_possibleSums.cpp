void possibleSums(vector<int>& coins, vector<int>& quantity, 
        unordered_set<int>& sums, int indx, int sum) {
    if (indx == coins.size()) {
        if (sum) sums.insert(sum);
        return;
    }
    for (int i = 0; i <= quantity[indx]; ++i) {
        possibleSums(coins, quantity, sums, indx + 1, sum + coins[indx] * i);
    }
}