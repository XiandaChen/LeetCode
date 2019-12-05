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
        for (int i = 0; i < n; ++i) {
            // chars previously read had been copyied to buf, read4() again
            if (readCnt == copyIndx) { 
                readCnt = read4(read4buf);
                copyIndx = 0; // reset to 0, must here
                if (readCnt == 0) return i; // end of file
                // copyIndx = 0; // error if here
            }
            buf[i] = read4buf[copyIndx++]; // copy from read4buf to buf
        }
        return n;
    }
private:
    // to hold chars everytime read from read4()
    char read4buf[4]; 
    // readCnt: actual num of chars by read4()
    // copyIndx: char indx being copied from read4buf to buf
    int readCnt = 0, copyIndx = 0; 
};