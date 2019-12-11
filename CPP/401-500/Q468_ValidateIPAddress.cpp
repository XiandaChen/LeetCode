class Solution {
public:
    string validIPAddress(string IP) {
        istringstream iss(IP);
        string t = ""; // to store substring b/w '.' (or ':')
        int cnt  = 0; // IPv4: cnt=4; IPv6: cnt=6
        if (IP.find(':') == string::npos) { // not found ':', is IPv4
            while (getline(iss, t, '.')) { // get string seperate by '.'
                ++cnt;
                if (cnt > 4 || t.empty() || t.size() > 3 || (t.size() > 1 && t[0] == '0'))
                    return "Neither";
                for (char c : t)
                    if (c < '0' || '9' < c) return "Neither";
                if(stoi(t) < 0 || 255 < stoi(t)) return "Neither"; // is stoi(), not atoi()
            }
            // check if last char is '.'
            return (cnt == 4 && IP.back() != '.') ? "IPv4" : "Neither";
        }
        else { // IPv6
            while (getline(iss, t, ':')) {
                ++cnt;
                if (cnt > 8 || t.empty() || t.size() > 4) return "Neither";
                for (char c : t)
                    if (!('0' <= c && c <= '9') && !('a' <= c && c <= 'f')
                       && !('A' <= c && c <= 'F')) return "Neither";
            }
            // check if last char is ':'
            return (cnt == 8 && IP.back() != ':') ? "IPv6" : "Neither";
        }
    }
};