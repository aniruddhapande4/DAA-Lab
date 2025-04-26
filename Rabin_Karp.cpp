#include <iostream>
#include <string>
#include <climits>
using namespace std;

void detectSubstring(string target, string base, int primeMod) {
    int lenTarget = target.length();
    int lenBase = base.length();
    int hashTarget = 0, hashWindow = 0;
    int shiftFactor = 1;
    int alphabetSize = 256;

    for (int i = 0; i < lenTarget - 1; i++)
        shiftFactor = (shiftFactor * alphabetSize) % primeMod;

    for (int i = 0; i < lenTarget; i++) {
        hashTarget = (alphabetSize * hashTarget + target[i]) % primeMod;
        hashWindow = (alphabetSize * hashWindow + base[i]) % primeMod;
    }

    for (int k = 0; k <= lenBase - lenTarget; k++) {
        if (hashTarget == hashWindow) {
            int l = 0;
            while (l < lenTarget && base[k + l] == target[l])
                l++;
            if (l == lenTarget)
                cout << "Match located at: " << k << endl;
        }

        if (k < lenBase - lenTarget) {
            hashWindow = (alphabetSize * (hashWindow - base[k] * shiftFactor) + base[k + lenTarget]) % primeMod;
            if (hashWindow < 0)
                hashWindow = (hashWindow + primeMod);
        }
    }
}

int main() {
    string text = "LOOKFORLOOKLOOKLOOKFORLOOK";
    string pattern = "LOOK";
    int mod = INT_MAX;

    detectSubstring(pattern, text, mod);
    return 0;
}
