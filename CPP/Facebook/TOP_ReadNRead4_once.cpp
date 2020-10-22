class Solution {
public:
    int read(char *buf, int n) {
        char read4buf[4];
        int read4cnt = 0, copyidx = 0;
        for (int i = 0; i < n; ++i) {
            if (copyidx == read4cnt) { // previous read4() had been copied
                read4cnt = read4(read4buf);
				copyidx = 0; // to copy the new read4buf
                if (read4cnt == 0) return i; // end of file
            }
            buf[i] = read4cnt[copyidx++];
        }
        return n;
    }
};