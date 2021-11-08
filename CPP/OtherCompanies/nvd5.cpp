#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'segment' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER x
 *  2. INTEGER_ARRAY space
 */

// [8,2,4,6], x=2
// [8,2] [2,4] [4,6]
// min=2, (4>2)2, 
// max=2, 2

int segment(int x, vector<int> space) {
    int n = space.size();
    
    //1 1 100000 x=1
    
    int maxval = INT_MIN;  // -2147483648
    for (int i = 0; i < n - x; i++) {   // o(n^2)
    
        int minval = INT_MAX;
    
        for (int j = i; j < i + x; j++) {
            if (space[j] <= minval) minval = space[j];  // 
            cout << "j = " << j << "; " << space[j] << " " <<  minval << endl;
            
        }  
        
        cout << minval << " " << maxval << endl;
         
        if (minval > maxval) maxval = minval;      
    }

    return maxval;
}

// i left

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string x_temp;
    getline(cin, x_temp);

    int x = stoi(ltrim(rtrim(x_temp)));

    string space_count_temp;
    getline(cin, space_count_temp);

    int space_count = stoi(ltrim(rtrim(space_count_temp)));

    vector<int> space(space_count);

    for (int i = 0; i < space_count; i++) {
        string space_item_temp;
        getline(cin, space_item_temp);

        int space_item = stoi(ltrim(rtrim(space_item_temp)));

        space[i] = space_item;
    }

    int result = segment(x, space);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
