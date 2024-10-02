#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdint>

using namespace std;

class NaiveBayes
{
private:
    unordered_map<string, std::int32_t> spamWordCount;
    unordered_map<string, std::int32_t> hamWordCount;
    std::int32_t spamCount;
    std::int32_t hamCount;

public:
    NaiveBayes() : spamCount(0), hamCount(0) {}

    void train(const vector<pair<string, string>> &trainingData)
    {
        for (const auto &data : trainingData)
        {
            const string &email = data.first;
            const string &label = data.second;

            istringstream iss(email);
            string word;
            while (iss >> word)
            {
                if (label == "spam")
                {
                    spamWordCount[word]++;
                    spamCount++;
                }
                else
                {
                    hamWordCount[word]++;
                    hamCount++;
                }
            }
        }
    }

    string predict(const string &email)
    {
        double spamProbability = log(static_cast<double>(spamCount) / (spamCount + hamCount));
        double hamProbability = log(static_cast<double>(hamCount) / (spamCount + hamCount));

        istringstream iss(email);
        string word;
        while (iss >> word)
        {
            // Calculate probabilities for each word
            double pSpam = static_cast<double>(spamWordCount[word] + 1) / (spamCount + 2); // Laplace smoothing
            double pHam = static_cast<double>(hamWordCount[word] + 1) / (hamCount + 2);    // Laplace smoothing

            spamProbability += log(pSpam);
            hamProbability += log(pHam);
        }

        return (spamProbability > hamProbability) ? "spam" : "ham";
    }
};

int main()
{
    NaiveBayes classifier;

    // Sample training data: (email content, label)
    vector<pair<string, string>> trainingData = {
        {"Free money now", "spam"},
        {"Limited time offer", "spam"},
        {"Hi, how are you?", "ham"},
        {"Important information regarding your account", "ham"},
        {"Congratulations! You've won a lottery", "spam"},
        {"Let's meet for lunch", "ham"}};

    classifier.train(trainingData);

    // Test the classifier
    string testEmail = "Congratulations! You have won free money";
    string result = classifier.predict(testEmail);

    cout << "The email is classified as: " << result << endl;

    return 0;
}