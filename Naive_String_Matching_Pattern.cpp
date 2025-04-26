#include <bits/stdc++.h>
using namespace std;

void naivePatternSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) {
            cout << "Pattern found at index " << i << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Pattern not found in the text." << endl;
}

int main() {
    string text1 = "THIS IS A TEST TEXT";
    string pattern1 = "TEST";
    cout << "Input: text = \"" << text1 << "\", pattern = \"" << pattern1 << "\"" << endl;
    cout << "Output: ";
    naivePatternSearch(text1, pattern1);

    cout << endl;

    string text2 = "AABAACAADAABAABA";
    string pattern2 = "AABA";
    cout << "Input: text = \"" << text2 << "\", pattern = \"" << pattern2 << "\"" << endl;
    cout << "Output: ";
    naivePatternSearch(text2, pattern2);

    return 0;
}
