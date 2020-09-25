class Solution {
public:
    int diameter(Node* root) {
        if (!root) return 0;
        int res = 0;
        getHeight(root, res);
        return res;
    }
    int getHeight(Node * node, int & res) {
        if (!node) return 0;
        int firstMax = 0, secondMax = 0;
        for (auto child : node->children) {
            int height = getHeight(child, res);
            if (height >= firstMax) {
                secondMax = firstMax;
                firstMax =  height;
            }
            else if (height > secondMax) {
                secondMax = height;
            }
        }
        res = max(res, firstMax + secondMax);
        return 1 + firstMax;
    }
};