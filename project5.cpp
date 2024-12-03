#include <iostream>
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

// Sort tokens by frequency (descending) then alphabetically
struct CompareByFrequency {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) const {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    }
};

int main() {
    // First pass: Count frequencies
    unordered_map<string, int> tokenFreq;
    string token;
    char aChar;

    // Read from stdin character by character
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
        }
    }

    // Create sorted map based on frequency
    map<pair<string, int>, string, CompareByFrequency> sortedMap;
    for (const auto& pair : tokenFreq) {
        sortedMap[{pair.first, pair.second}] = pair.first;
    }

    // Create position mapping
    unordered_map<string, int> tokenToPosition;
    int position = 1;
    for (const auto& pair : sortedMap) {
        tokenToPosition[pair.first.first] = position++;
    }

    // Print sorted tokens
    for (const auto& pair : sortedMap) {
        cout << pair.first.first << " ";
    }
    cout << endl << "**********" << endl;

    // Reset cin to beginning of input
    cin.clear();
    cin.seekg(0);

    // Second pass: Print positions
    bool firstToken = true;
    while (cin.get(aChar)) {
        while (!cin.eof() && isDelimiter(aChar)) {
            if (!cin.get(aChar)) break;
        }
        if (cin.eof()) break;

        token.clear();
        while (!cin.eof() && !isDelimiter(aChar)) {
            token += aChar;
            if (!cin.get(aChar)) break;
        }
        if (!token.empty()) {
            if (!firstToken) {
                cout << " ";
            }
            cout << tokenToPosition[token];
            firstToken = false;
        }
    }
    cout << endl;

    return 0;
}
