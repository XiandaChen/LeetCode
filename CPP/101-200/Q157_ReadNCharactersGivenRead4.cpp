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
            // character previously read4() have been move to buf
            if (copyIndx == read4Cnt) { // read4() new characters
                read4Cnt = read4(read4buf);
                if (read4Cnt == 0) return i;
                copyIndx = 0; // initial copyIndx
            }
            buf[i] = read4buf[copyIndx++];
        }
        return n;
    }
};