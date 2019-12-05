// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        char read4buf[4];
        int read4Cnt = 0, copyIndx = 0;
        for (int i = 0; i < n; ++i) {
            if (read4Cnt == copyIndx) {
                read4Cnt = read4(read4buf);
                copyIndx = 0;
                if (read4Cnt == 0) return i;
            }
            buf[i] = read4buf[copyIndx++];
        }
        return n;
    }
};