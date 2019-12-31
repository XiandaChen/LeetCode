class Solution {
public:
    int nthUglyNumber(int n, int A, int B, int C) {
        long a = long(A), b = long(B), c = long(C); // must done for bc in lcm()
        long ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c), abc = lcm(a, bc);
        long left = 1, right = INT_MAX;
        while (left < right) {
            long mid = left + (right - left) / 2;
            // num of ugly numbers that are <= mid
            long k = mid / a + mid / b + mid / c 
                    - (mid / ab + mid / ac + mid / bc)
                    + mid / abc;
            if (k >= n) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};

/*
Implement lcm (least common multiple) using gcd (greatest common divisor)

int gcd(int a, int b){ 
    if (b == 0) 
        return a;  
    return gcd(b, a % b);  
} 

int lcm(int a, int b) {  
	return (a * b) / gcd(a, b);  
}  
*/