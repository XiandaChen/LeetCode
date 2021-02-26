class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int index = 0, n = words.size();
        
        while (index < n) {
            // step 1: decide #words in the same line
            int totalChars = words[index].size(), last = index + 1;
            while (last < n && totalChars + words[last].size() + 1 <= maxWidth) {
                totalChars += 1 + words[last].size();  // 1 for ' '
                ++last; // when break, last is startIdx for next line
            }
            
            // step 2: construct the line
            string line;
            int gaps = last - index - 1; 
            // last line, or line with only one word
            // last line: left justified and no extra space is inserted b/w words.
            if (last == n || gaps == 0) { 
                for (int i = index; i < last - 1; ++i) {
                    line.append(words[i]);
                    line.append(" "); // " ", not ' '
                }
                line.append(words[last - 1]); // last word in the line
                if (line.size() < maxWidth) { // padding spaces at the end
                    line.append(maxWidth - line.size(), ' '); 
                }
            }
            else {  
                // no-last line: extra spaces are evenly distributed b/w words
                // # of extra spaces = (maxWidth - totalChars) / gaps
                int spaces = (maxWidth - totalChars) / gaps;
                int remain = (maxWidth - totalChars) % gaps;
                for (int i = index; i < last - 1; ++i) {
                    line.append(words[i]);
                    line.append(" ");
                    
                    // padding extra spaces b/w words
                    line.append(spaces, ' ');
                    if (i - index < remain) { // if not even, the left will be assigned more spaces
                        line.append(" "); 
                    }
                }
                line.append(words[last - 1]); // last word in the line
            }
            
            res.push_back(line);
            index = last;
        }
        
        return res;
    }
};

