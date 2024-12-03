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
    // First pass: Count frequencies
    unordered_map<string, int> tokenFreq;
    multimap<int, string, greater<int>> freqToToken;
    map<string, int> tokenToPosition;
    string token;
    char aChar;

    // Store original tokens with their positions
    string originalInput;

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
            originalInput += token + " ";
        }
    }

    // Sort tokens by frequency using multimap
    for (const auto& pair : tokenFreq) {
        freqToToken.insert({pair.second, pair.first});
    }

    // Create position mapping
    int position = 1;
    for (const auto& pair : freqToToken) {
        tokenToPosition[pair.second] = position++;
    }

    // Print sorted tokens with newline after 80 characters
    int charCount = 0;
    for (const auto& pair : freqToToken) {
        if (charCount + pair.second.length() + 1 > 84) {
            cout << endl;
            charCount = 0;
        }
        cout << pair.second << " ";
        charCount += pair.second.length() + 1;
    }
    cout << endl << "**********" << endl;

    // Second pass: Print positions
    charCount = 0;
    bool firstToken = true;
    token.clear();

    // Process stored input for positions
    for (size_t i = 0; i < originalInput.length(); i++) {
        if (originalInput[i] == ' ') {
            if (!token.empty()) {
                if (!firstToken) {
                    if (charCount + to_string(tokenToPosition[token]).length() + 1 > 84) {
                        cout << endl;
                        charCount = 0;
                    }
                    charCount++;
                }
                cout << tokenToPosition[token] << " ";
                charCount += to_string(tokenToPosition[token]).length();
                firstToken = false;
                token.clear();
            }
        } else {
            token += originalInput[i];
        }
    }
    cout << endl;

    return 0;
}
