// groupingDishes
// group the dishes by ingredients, so that for each ingredient 
// you'll be able to find all the dishes that contain it (if there are at least 2 such dishes)

// dishes = [["Salad", "Tomato", "Cucumber", "Salad", "Sauce"],
            // ["Pizza", "Tomato", "Sausage", "Sauce", "Dough"],
            // ["Quesadilla", "Chicken", "Cheese", "Sauce"],
            // ["Sandwich", "Salad", "Bread", "Tomato", "Cheese"]]
// groupingDishes(dishes) = [["Cheese", "Quesadilla", "Sandwich"],
                            // ["Salad", "Salad", "Sandwich"],
                            // ["Sauce", "Pizza", "Quesadilla", "Salad"],
                            // ["Tomato", "Pizza", "Salad", "Sandwich"]]
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<string>> groupingDishes (vector<vector<string>>& dishes) {
    map<string, set<string>> groups; // ingredient - dishes
    vector<vector<string>> res;
    for (int i = 0; i < (int)dishes.size(); ++i) {
        for (int j = 1; j < (int)dishes[i].size(); ++j) {
            groups[dishes[i][j]].insert(dishes[i][0]);
        }
    }
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        if (it->second.size() <= 1) continue; // there are at least 2 such dishes
        vector<string> tmp;
        tmp.push_back(it->first);
        for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
            tmp.push_back(*jt);
        }
        res.push_back(tmp);
    }
    return res;
}

int main() {
    vector<vector<string>> dishes = {{"Salad", "Tomato", "Cucumber", "Salad", "Sauce"},
            {"Pizza", "Tomato", "Sausage", "Sauce", "Dough"},
            {"Quesadilla", "Chicken", "Cheese", "Sauce"},
            {"Sandwich", "Salad", "Bread", "Tomato", "Cheese"}};
    vector<vector<string>> res = groupingDishes(dishes);
    for (int i = 0; i < (int)res.size(); ++i) {
        for (int j = 0; j < (int)res[i].size(); ++j) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
