#include <fstream>
#include <cstring>
#include <vector>
#define MAXALPHABET 26
#define MAXLEN 100000
using namespace std;

ifstream fin("encryption.in");
ofstream fout("encryption.out");

// Function to calculate the frequency of a given letter in a specific word.
int calculateFreqPerWord(char letter, vector<string> words, int index) {
    int freq = 0;
    int sizeOfWord = words[index].size();

    for (int i = 0; i < sizeOfWord; i++) {
        if (words[index][i] == letter) {
            freq++;
        }
    }

    return freq;
}

// Function to sort words in descending order based on the frequency of a given letter.
// If two words have the same frequency, they are further sorted based on the ratio of occurrences to word length.
// If the ratios are also equal, the longer word is prioritized.
vector<string> sortDescending(int start, int end, char letter, vector<string> words) {
    int freq[MAXLEN] = {0};
    double ratio[MAXLEN] = {0.0};

    // Calculate the frequency of the given letter in each word.
    for (int i = start; i < end; i++) {
        freq[i] = calculateFreqPerWord(letter, words, i);
    }

    // Sort words by frequency in descending order.
    for (int i = start; i < end - 1; i++) {
        for (int j = i + 1; j < end; j++) {
            if (freq[i] < freq[j]) {
                swap(freq[i], freq[j]);
                swap(words[i], words[j]);
            }
        }
    }

    // Compute the frequency-to-length ratio for each word.
    for (int i = start; i < end; i++) {
        ratio[i] = (double)freq[i] / words[i].size();
    }

    // Sort words based on their ratio in descending order.
    // If two words have the same ratio, the longer word is prioritized.
    for (int i = start; i < end - 1; i++) {
        for (int j = i + 1; j < end; j++) {
            if (ratio[i] < ratio[j]) {
                swap(ratio[i], ratio[j]);
                swap(words[i], words[j]);
            } else if (!ratio[i] && ratio[i] == ratio[j]) {
                if (words[i].size() < words[j].size()) {
                    swap(words[i], words[j]);
                }
            }
        }
    }

    return words;
}

int main() {
    int N;
    fin >> N;

    vector<string> words;
    vector<int> lengths;
    int maxLength = INT32_MIN;

    // Read the list of words.
    for (int i = 0; i < N; i++) {
        string word;
        fin >> word;
        words.push_back(word);
    }

    int lengthTemp = 0, occurrencesTemp = 0;
    int totalLength, totalOccurrences;

    // Iterate through each letter in the alphabet to determine the optimal compression.
    for (char letter = 'a'; letter <= 'z'; letter++) {
        totalLength = 0;
        totalOccurrences = 0;
        words = sortDescending(0, N, letter, words);

        // Compute the maximum compression efficiency by checking if adding a word improves the compression ratio.
        for (int i = 0; i < N; i++) {
            occurrencesTemp = calculateFreqPerWord(letter, words, i);
            lengthTemp = words[i].size();

            if ((totalOccurrences + occurrencesTemp) * 2 > totalLength + lengthTemp) {
                totalOccurrences += occurrencesTemp;
                totalLength += lengthTemp;
            }
        }

        lengths.push_back(totalLength);
    }

    // Find the maximum compressed length among all letters.
    for (int i = 0; i < MAXALPHABET; i++) {
        if (lengths[i] > maxLength) {
            maxLength = lengths[i];
        }
    }

    fout << maxLength << endl;
    fin.close();
    fout.close();

    return 0;
}
