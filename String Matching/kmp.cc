#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

class KMP
{
public:
    KMP(const std::string &pattern) : pattern(pattern)
    {
        computeLPS();
    }

    void search(const std::string &text)
    {
        std::int32_t m = pattern.size();
        std::int32_t n = text.size();
        std::int32_t i = 0; // index for text
        std::int32_t j = 0; // index for pattern

        while (i < n)
        {
            if (pattern[j] == text[i])
            {
                i++;
                j++;
            }
            if (j == m)
            {
                std::cout << "Pattern found at index " << i - j << std::endl;
                j = lps[j - 1];
            }
            else if (i < n && pattern[j] != text[i])
            {
                if (j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    i++;
                }
            }
        }
    }

private:
    std::string pattern;
    std::vector<std::int32_t> lps;

    void computeLPS()
    {
        std::int32_t m = pattern.size();
        lps.resize(m);
        std::int32_t length = 0; // length of the previous longest prefix suffix
        lps[0] = 0;     // lps[0] is always 0

        for (int i = 1; i < m; i++)
        {
            while (length > 0 && pattern[length] != pattern[i])
            {
                length = lps[length - 1];
            }
            if (pattern[length] == pattern[i])
            {
                length++;
            }
            lps[i] = length;
        }
    }
};

int main()
{
    std::string text = "ACGTACGTGACGT";
    std::string pattern = "GAC";

    KMP kmp(pattern);
    kmp.search(text);

    return 0;
}