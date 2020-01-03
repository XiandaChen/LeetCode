class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area1 = (C - A) * (D - B), area2 = (G - E) * (H - F);
        if (C <= E || D <= F || G <= A || H <= B) 
            return area1 + area2;
        return area1 - ((min(G, C) - max(A, E)) * (min(D, H) - max(B, F))) + area2;
        // error, (area1  + area2) > INT_MAX
        // return area1  + area2 - ((min(G, C) - max(A, E)) * (min(D, H) - max(B, F)));
    }
};