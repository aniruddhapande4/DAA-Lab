#include <iostream>
#include <string>
using namespace std;

#define CHAR_LIMIT 256

void buildLastOccurTable(string needle, int len, int lastOccur[CHAR_LIMIT]) {
    for (int k = 0; k < CHAR_LIMIT; k++)
        lastOccur[k] = -1;

    for (int k = 0; k < len; k++)
        lastOccur[(int)needle[k]] = k;
}

void locatePattern(string source, string needle) {
    int lenPattern = needle.length();
    int lenSource = source.length();
    int lastOccur[CHAR_LIMIT];

    buildLastOccurTable(needle, lenPattern, lastOccur);

    int offset = 0;

    while (offset <= (lenSource - lenPattern)) {
        int idx = lenPattern - 1;

        while (idx >= 0 && needle[idx] == source[offset + idx])
            idx--;

        if (idx < 0) {
            cout << "Match at position: " << offset << endl;
            offset += (offset + lenPattern < lenSource) ? lenPattern - lastOccur[source[offset + lenPattern]]: 1;
        } else {
            offset += max(1, idx - lastOccur[source[offset + idx]]);
        }
    }
}

int main() {
    string sourceText = "TEXTPATTERNTEXTPATTERNMATCHPATTERN";
    string findThis = "PATTERN";

    locatePattern(sourceText, findThis);
    return 0;
}
