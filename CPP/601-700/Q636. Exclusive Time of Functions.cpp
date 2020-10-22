class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        stack<int> st; // func_id
        int pretime = 0;
        for (auto log : logs) {
            int pos1 = log.find(':'), pos2 = log.find_last_of(':');
            int id = stoi(log.substr(0, pos1));
            string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
            int curtime = stoi(log.substr(pos2 + 1));
            
            if (type == "start") {
                if (!st.empty()) {
                    // suspend cur func
                    res[st.top()] += curtime - pretime; // start: very start of the time slot
                }
                st.push(id);
                pretime = curtime;
            }
            else { // "end"
                res[st.top()] += curtime - pretime + 1; // +1: end time: very end of the time slot
                st.pop();
                pretime = curtime + 1; // next log starts for next time slot
            }
        }
        return res;
    }
};