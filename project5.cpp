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
    string filename = "input1.txt";

    // First pass: Count frequencies
    ifstream myInputFile(filename);
    if (!myInputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    unordered_map<string, int> tokenFreq;
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
        }
    }
    myInputFile.close();

    // Sort tokens
    vector<pair<string, int>> sortedTokens(tokenFreq.begin(), tokenFreq.end());
    sort(sortedTokens.begin(), sortedTokens.end(), compareByFrequency);

    // Create position mapping
    unordered_map<string, int> tokenToPosition;
    for (size_t i = 0; i < sortedTokens.size(); i++) {
        tokenToPosition[sortedTokens[i].first] = i + 1;
    }

//    cout << "___________________________________________________________________________________" << endl;

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

 //   cout << "___________________________________________________________________________________" << endl;

    // Second pass: Print positions
    myInputFile.open(filename);
    if (!myInputFile.is_open()) {
        cerr << "Error reopening file: " << filename << endl;
        return 1;
    }

    // Read tokens again and print positions with newline after 80 characters
    bool firstToken = true;
    charCount = 0;
    while (myInputFile.get(aChar)) {
        while (!myInputFile.eof() && isDelimiter(aChar)) {
            if (!myInputFile.get(aChar)) break;
        }
        if (myInputFile.eof()) break;

        token.clear();
        while (!myInputFile.eof() && !isDelimiter(aChar)) {
            token += aChar;
            if (!myInputFile.get(aChar)) break;
        }
        if (!token.empty()) {
            if (!firstToken) {
                if (charCount + to_string(tokenToPosition[token]).length() + 1 > 85) {
                    cout << endl;
                    charCount = 0;
                }
                //cout << " ";
                charCount++;
            }
            cout << tokenToPosition[token] << " ";
            charCount += to_string(tokenToPosition[token]).length();
            firstToken = false;
        }
    }
    cout << endl;

    return 0;
}
