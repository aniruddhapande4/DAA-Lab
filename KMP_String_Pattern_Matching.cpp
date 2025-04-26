#include <iostream>
#include <string>
#include <vector>
using namespace std;

void constructLps(string &pat, vector<int> &lps) {

    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pat.length()) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // Display the LPS (pi) table
    cout << "\nLPS (pi) table:\n";
    cout << "Index:   ";
    for (int i = 0; i < pat.length(); i++) {
        cout << i << " ";
    }
    cout << "\nPattern: ";
    for (char c : pat) {
        cout << c << " ";
    }
    cout << "\nLPS:     ";
    for (int val : lps) {
        cout << val << " ";
    }
    cout << "\n";
}

vector<int> search(string &pat, string &txt) {
    int n = txt.length();
    int m = pat.length();

    vector<int> lps(m);
    vector<int> res;

    constructLps(pat, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (txt[i] == pat[j]) {
            i++;
            j++;
            if (j == m) {
                res.push_back(i - j);
                j = lps[j - 1];
            }
        } else {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return res;
}

int main() {
    string txt = "aabaaacaadaabaaba";
    string pat = "aabaa";

    vector<int> res = search(pat, txt);

    cout << "\nPattern found at indices: ";
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";

    return 0;
}
