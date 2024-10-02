#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

class BoyerMoore
{
public:
    BoyerMoore(const std::string &pattern) : pattern(pattern)
    {
        buildBadCharTable();
    }

    void search(const std::string &text)
    {
        std::int32_t m = pattern.size();
        std::int32_t n = text.size();
        std::int32_t skip;

        for (std::int32_t i = 0; i <= n - m;)
        {
            skip = 0;
            for (std::int32_t j = m - 1; j >= 0; j--)
            {
                if (pattern[j] != text[i + j])
                {
                    skip = std::max(1, j - badCharTable[text[i + j]]);
                    break;
                }
            }
            if (skip == 0)
            {
                std::cout << "Pattern found at index " << i << std::endl;

                // Move to the next character after the found match
                skip = 1; 
            }
            i += skip;
        }
    }

private:
    std::string pattern;
    std::unordered_map<char, std::int32_t> badCharTable;

    void buildBadCharTable()
    {
        std::int32_t m = pattern.size();
        for (std::int32_t i = 0; i < m; i++)
        {
            // Store the last occurrence of each character
            badCharTable[pattern[i]] = i;
        }
    }
};

int main()
{
    std::string text = "ACGTDACGTDGACGT";
    std::string pattern = "GAC";

    BoyerMoore bm(pattern);
    bm.search(text);

    return 0;
}