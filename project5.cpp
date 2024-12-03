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
    unordered_map<string, int> tokenFreq;  // Store token frequencies
    string token;
    char aChar;

    // First pass: Count frequencies
    while (cin.get(aChar)) {
        // Skip delimiters
        while (!cin.eof() && isDelimiter(aChar)) {
            if (!cin.get(aChar)) break;
        }
        if (cin.eof()) break;

        // Build token (including punctuation)
        token.clear();
        while (!cin.eof() && !isDelimiter(aChar)) {
            token += aChar;
            if (!cin.get(aChar)) break;
        }
        if (!token.empty()) {
            tokenFreq[token]++;
        }
    }

    // Sort tokens by frequency (descending) and then alphabetically
    multimap<pair<int, string>, string, greater<pair<int, string>>> sortedTokens;
    for (const auto& pair : tokenFreq) {
        sortedTokens.insert({{pair.second, pair.first}, pair.first});
    }

    // Print sorted tokens
    for (const auto& pair : sortedTokens) {
        cout << pair.second << " ";
    }
    cout << endl << "**********" << endl;

    // Create position mapping
    unordered_map<string, int> tokenToPosition;
    int position = 1;
    for (const auto& pair : sortedTokens) {
        tokenToPosition[pair.second] = position++;
    }

    // Reset input stream
    cin.clear();
    cin.seekg(0);

    // Second pass: Print positions
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
            cout << tokenToPosition[token] << " ";
        }
    }
    cout << endl;

    return 0;
}
