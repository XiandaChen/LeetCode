class Solution {
public:
    string simplifyPath(string path) {
        vector<string> v; // to hold substrs
        string res;
        // seperate string using '/' or '////..'
        int i = 0;
        while (i < path.size()) {
            while (path[i] == '/' && i < path.size()) ++i;
            if (i == path.size()) break; // must check
            int start = i;
            while (path[i] != '/' && i < path.size()) ++i;
            int end = i - 1;
            string ss = path.substr(start, end - start + 1);
            if (ss == "..") { 
                if (!v.empty()) v.pop_back();
            } // must use {} to seperate, otherwise "else if" match
            else if (ss != ".") v.push_back(ss);
        }
        if (v.empty()) return "/";
        for (int i = 0; i < v.size(); ++i) {
            res += '/' + v[i];
        }
        return res;
    }
};