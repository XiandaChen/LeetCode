// IsCryptSolution
// Given [word1, word2, word3], check word1+word2=word3, containing no numbers with leading zeroes
// For crypt = ["SEND", "MORE", "MONEY"] and 
// solution = [['O', '0'],
//             ['M', '1'],
//             ['Y', '2'],
//             ['E', '5'],
//             ['N', '6'],
//             ['D', '7'],
//             ['R', '8'],
//             ['S', '9']]
// the output should be
// isCryptSolution(crypt, solution) = true, since 9567 + 1085 = 10652.
            
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isCryptSolution (vector<string>& crypt, vector<vector<char>>& solution) {
    for (string & s : crypt) {
        for (vector<char> sol : solution) replace(s.begin(), s.end(), sol[0], sol[1]); // #include <algorithm>
    }
    
    for (string s : crypt) {
        if (s[0] == '0' && s.size() > 1) return false;
    }
    
    return stoi(crypt[0]) + stoi(crypt[1]) == stoi(crypt[2]);

}

int main() {
    vector<vector<char>> solution = {{'O', '0'}, {'M', '1'}, {'Y', '2'},
                                {'E', '5'}, {'N', '6'}, {'D', '7'},
                                {'R', '8'}, {'S', '9'}};
    vector<string> crypt = {"SEND", "MORE", "MONEY"};
    
    if (isCryptSolution(crypt, solution))
        cout << "True" << endl;
    else 
        cout << "False" << endl;
    
    return 0;
}
