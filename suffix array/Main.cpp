#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string.h>

using namespace std;

int main()
{
    /*Base sequence*/
    string s;
    string target;
    //cout << "Please enter your sequence:" << endl;
    cin >> s;                                                               // Take first input sequence
    cin >> target;                                                          // Take second input sequence
    int length = s.length();                                                // Store length value for later use
    string copyS = s;
    /*Convert and store into suffix array, sorting as well*/
    vector<string> row;                                                     // Using vector to store values
    row.assign(length, "0");                                                 // Initialize all cells to "0"
    vector<vector<string>> dataSet;                                         // 2D vector to form the data set storage
    dataSet.assign(2, row);                                                  // Assign space and initialize for each row

    //cout << "\nThe suffix list: " << endl;
    //cout << "Position | Suffix " << endl;
    for (int i = 0; i < length; i++) {
        dataSet[0][i].assign(s);                                            // Put sequence S into vector storage
        s.erase(s.begin());                                                 // Erase first character of S to simulate other suffix(s)
        //cout << dataSet[0][i] << endl;
    }

    /*Sort the data base and do LCP calculation*/
    sort(dataSet[0].begin(), dataSet[0].end());                             // Using C++ sort algorithm to sort the suffix(s)
    //cout << endl <<"The sorted suffix list: " << endl;
    for (int i = 0; i < length; i++) {
        bool go = true;
        int numb = 0;
        while (go && i > 0) {                                                 // Maximum number of comparison = length of shorter sub-sequence
            dataSet[1][i].assign(to_string(numb));
            if (dataSet[0][i][numb] != dataSet[0][i - 1][numb]) go = false;   // LCP of upward comparison
            if (numb + 1 >= dataSet[0][i - 1].length()) go = false;            // If two characters are not equal || reaching maximum number -->> LCP stop
            numb++;                                                         // numb++, means having a longer common prefix
        }

        go = true;                                                          // Reset variables
        numb = 0;

        while (go && i > 0 && i < (length - 1)) {                                 // LCP of downward comparison
            dataSet[1][i].assign(to_string(max(numb, stoi(dataSet[1][i])))); // Only take the max score of two LCP comparison
            if (dataSet[0][i][numb] != dataSet[0][i + 1][numb]) go = false;   // Break when the condition is not true
            if (numb + 1 >= dataSet[0][i].length()) go = false;              // Break when reaching maximum number
            numb++;
        }

        cout << copyS[length - dataSet[0][i].length() - 1] << "  |  " << dataSet[0][i] << endl;
    }

    /*Calculate and print out leaf nodes position*/
    for (int i = 0; i < length; i++) {
        cout << length - (dataSet[0][i].length() - stoi(dataSet[1][i])) + 1 << "-" << length << endl;
    }
    /*Check for demanded sub-sequence*/
    bool match = true;                                                      // Two boolean :
    bool searched = false;                                                  // match = found exact sub-string
    for (int i = 0; i < length; i++) {                                      // searched = does it actual do a search or just all skipped
        match = true;
        searched = false;
        char first = target[0];
        if (first == dataSet[0][i][0]) {                                    // linear search to a point until at least the first character matches
            searched = true;                                                // Too lazy to implement a binary search / Interval serach :P
            for (int j = 1; j < target.length(); j++) {                     // Matching until whole target sequence ends
                if (target[j] != dataSet[0][i][j]) match = false;           // return false boolean value if one character is found not matching
            }
            if (searched && match) {
                cout << "Yes" << endl;
                break;                                                      // Result print out
            }
        }
    }
    if (!searched || !match) cout << "No";
    return 0;
}
