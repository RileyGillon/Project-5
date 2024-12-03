#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Check if character is a delimiter (space or newline)
bool isDelimiter(char c) {
    return c == ' ' || c == '\n';
}

// Sort tokens by frequency (descending) then alphabetically
bool compareByFrequency(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int main() {
    // First pass: Count frequencies
    unordered_map<string, int> tokenFreq;
    vector<string> originalTokens;  // Store original tokens for second pass
    string token;
    char aChar;

    // Read from standard input character by character
    while (cin.get(aChar)) {
        // Skip delimiters
        while (cin && isDelimiter(aChar)) {
            if (!cin.get(aChar)) break;
        }
        if (!cin) break;

        // Build token
        token.clear();
        while (cin && !isDelimiter(aChar)) {
            token += aChar;
            if (!cin.get(aChar)) break;
        }
        if (!token.empty()) {
            tokenFreq[token]++;
            originalTokens.push_back(token);  // Store token for second pass
        }
    }

    // Sort tokens
    vector<pair<string, int>> sortedTokens(tokenFreq.begin(), tokenFreq.end());
    sort(sortedTokens.begin(), sortedTokens.end(), compareByFrequency);

    // Create position mapping
    unordered_map<string, int> tokenToPosition;
    for (size_t i = 0; i < sortedTokens.size(); i++) {
        tokenToPosition[sortedTokens[i].first] = i + 1;
    }

    // Print sorted tokens with newline after 80 characters
    int charCount = 0;
    for (const auto& pair : sortedTokens) {
        if (charCount + pair.first.length() + 1 > 84) {
            cout << endl;
            charCount = 0;
        }
        cout << pair.first << " ";
        charCount += pair.first.length() + 1;
    }
    cout << endl << "**********" << endl;

    // Second pass: Print positions using stored tokens
    charCount = 0;
    bool firstToken = true;

    for (const string& storedToken : originalTokens) {
        if (!firstToken) {
            if (charCount + to_string(tokenToPosition[storedToken]).length() + 1 > 84) {
                cout << endl;
                charCount = 0;
            }
            charCount++;
        }
        cout << tokenToPosition[storedToken] << " ";
        charCount += to_string(tokenToPosition[storedToken]).length();
        firstToken = false;
    }
    cout << endl;

    return 0;
}
