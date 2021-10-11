/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
public:
    int findCelebrity(int n) {
        for (int i = 0; i < n; i++) { // check if i is celebrity
            int j = 0;
            
            // i is celebrity if only if i knows no one and all other j knows i
            for (; j < n; j++) { 
                if (i != j && (knows(i, j) || !knows(j, i))) break; // i is not celebrity
            }
            
            if (j == n) return i;
        }
        
        return -1;
    }
};