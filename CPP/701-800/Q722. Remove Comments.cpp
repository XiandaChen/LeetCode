class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> res;
        string out = "";
        bool blocked = false;
        
        for (auto & line : source) {
            int len = line.size();
            for (int i = 0; i < len; i++) {
                if (!blocked) { // if not commented yet
                    if (i == len - 1) out += line[i];
                    else {
                        string t = line.substr(i, 2);
                        if (t == "//") {
                            break; // the rest of the characters to the right is ignored
                        }
                        else if (t == "/*") {
                            blocked =  true;
                            ++i;  
                        }
                        else {
                            out += line[i];
                        }
                    }
                }
                else { // if blocked, find the end of block comment
                    if (i < len - 1) {
                        if (line.substr(i, 2) == "*/") {
                            blocked = false;
                            ++i;
                        }
                    }
                }
                
            }
            
            // add valid code in this line to result
            if (!blocked && !out.empty()) {
                res.push_back(out);
                out = "";
            }
        }
        
        return res;
    }
};