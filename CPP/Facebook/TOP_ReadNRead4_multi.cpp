class Solution {
public:
    int read(char *buf, int n) {
        for (int i = 0; i < n; ++i) {
            if (read4cnt == copyidx) {
                read4cnt = read4(read4buf);
                copyidx = 0; // must before if(..)
                if (read4cnt == 0) return i;
            }
            buf[i] = read4buf[copyidx++];
        }
        return n;
    }
private:
    char read4buf[4];
    int read4cnt = 0, copyidx = 0;
};