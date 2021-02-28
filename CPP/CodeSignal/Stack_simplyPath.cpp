class Solution {
public:
    string simplifyPath(string path) {
        vector<string> vec;
        string tmp;
        stringstream ss(path);
        
        // get all valid substr bwteen '/'
        while (getline(ss, tmp, '/')) {
            if (tmp == "" || tmp == "." || (tmp == ".." && vec.empty())) continue;
            else if (tmp == ".." && !vec.empty()) vec.pop_back();
            else vec.push_back(tmp);
        }
        
        if (vec.empty()) return "/";
        
        string res;
        for (string s : vec) {
            res += "/" + s;
        }
        
        return res;
    }
};