#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

// Check if character is a delimiter (space or newline)
bool isDelimiter(char c) {
    return c == ' ' || c == '\n';
}

int main() {
    unordered_map<string, int> tokenFreq;
    multimap<int, string> originalOrder;
    string token;
    char aChar;
    int position = 0;

    // Read standard input character by character
    while (cin.get(aChar)) {
        // Skip delimiters
        while (!cin.eof() && isDelimiter(aChar)) {
            if (!cin.get(aChar)) break;
        }
        if (cin.eof()) break;

        // Build token
        token.clear();
        while (!cin.eof() && !isDelimiter(aChar)) {
            token += aChar;
            if (!cin.get(aChar)) break;
        }
        if (!token.empty()) {
            tokenFreq[token]++;
            originalOrder.insert({position++, token});
        }
    }

    // Create frequency-based map (automatically sorted by frequency and alphabetically)
    map<pair<int, string>, string, greater<pair<int, string>>> freqSorted;
    for (const auto& pair : tokenFreq) {
        freqSorted[{pair.second, pair.first}] = pair.first;
    }

    // Print sorted tokens
    for (const auto& pair : freqSorted) {
        cout << pair.second << " ";
    }
    cout << endl << "**********" << endl;

    // Print original tokens in their original order
    for (const auto& pair : originalOrder) {
        cout << pair.second << " ";
    }
    cout << endl;

    return 0;
}
