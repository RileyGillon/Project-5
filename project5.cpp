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
    string filename = "testOutput.txt";

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

    // Second pass: Print positions
    myInputFile.open(filename);
    if (!myInputFile.is_open()) {
        cerr << "Error reopening file: " << filename << endl;
        return 1;
    }

    // Read tokens again and print positions
    bool firstToken = true;
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
                cout << " ";
            }
            cout << tokenToPosition[token];
            firstToken = false;
        }
    }
    cout << endl;

    return 0;
}
