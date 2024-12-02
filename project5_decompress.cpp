#include <iostream>
#include <fstream>
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
    string filename;
    cin >> filename;

    // First pass: Count frequencies and store original tokens
    ifstream myInputFile(filename);
    if (!myInputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    unordered_map<string, int> tokenFreq;
    vector<string> originalTokens;
    string token;
    char aChar;

    // Read file character by character
    while (myInputFile.get(aChar)) {
        // Skip delimiters
        while (!myInputFile.eof() && isDelimiter(aChar)) {
            if (!myInputFile.get(aChar)) break;
        }
        if (myInputFile.eof()) break;

        // Build token
        token.clear();
        while (!myInputFile.eof() && !isDelimiter(aChar)) {
            token += aChar;
            if (!myInputFile.get(aChar)) break;
        }
        if (!token.empty()) {
            tokenFreq[token]++;
            originalTokens.push_back(token);
        }
    }
    myInputFile.close();

    // Sort tokens
    vector<pair<string, int>> sortedTokens(tokenFreq.begin(), tokenFreq.end());
    sort(sortedTokens.begin(), sortedTokens.end(), compareByFrequency);

    // Print sorted tokens with newline after 83 characters
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

    // Print original tokens in their original order
    charCount = 0;
    for (const auto& originalToken : originalTokens) {
        if (charCount + originalToken.length() + 1 > 84) {
            cout << endl;
            charCount = 0;
        }
        cout << originalToken << " ";
        charCount += originalToken.length() + 1;
    }
    cout << endl;

    return 0;
}
