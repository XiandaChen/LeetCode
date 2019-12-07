class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0); // initial
        stack<int> st; // store fid of start logs
        int pretime = 0;
        for (string log : logs) {
            // split log, and extact fid:type:time
            int pos1 = log.find(":"); // the first ":"
            int pos2 = log.find_last_of(":"); // the last ":"
            int fid = stoi(log.substr(0, pos1));
            string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
            int curtime = stoi(log.substr(pos2 + 1));
            // when there is func runing, calculate its runing time 
            if (!st.empty()) {
                res[st.top()] += curtime - pretime;
            }
            pretime = curtime;
            if (type == "start") st.push(fid);
            else { // increase res[t] and pretime, since "end" takes 1 unit time
                int t = st.top(); st.pop();
                ++res[t];
                ++pretime;
            }
        }
        return res;
    }
};