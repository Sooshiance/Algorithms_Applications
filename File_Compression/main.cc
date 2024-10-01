#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

// Node structure for Huffman Tree
struct Node
{
    char ch;
    int freq;

    Node *left, *right;

    Node(char ch, int freq, Node *left = nullptr, Node *right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}
};

// Comparisson object for priority queue
struct Compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

// Function to build Huffman Tree
Node *buildHuffmanTree(unordered_map<char, int> &freqMap)
{
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (auto &pair : freqMap)
    {
        // push new nodes to queue
        pq.push(new Node(pair.first, pair.second));
    }
    while (pq.size() != 1)
    {
        // Calculate each node value
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }
    return pq.top();
}

// Function to generate Huffman Codes(recursion)
void generateCodes(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = str;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

// Function to compress file
void compressFile(const string &inputFile, const string &outputFile, unordered_map<char, int> &freqMap)
{
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    char ch;

    while (inFile.get(ch))
    {
        freqMap[ch]++;
    }

    Node *root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCode;

    generateCodes(root, "", huffmanCode);

    inFile.clear();
    inFile.seekg(0);

    string encodedStr = "";

    while (inFile.get(ch))
    {
        encodedStr += huffmanCode[ch];
    }

    outFile << encodedStr;

    inFile.close();
    outFile.close();
}

// Function to decompress file
void decompressFile(const string &inputFile, const string &outputFile, Node *root)
{
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    Node *curr = root;
    char bit;
    while (inFile.get(bit))
    {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right)
        {
            outFile.put(curr->ch);
            curr = root;
        }
    }
    inFile.close();
    outFile.close();
}

int main()
{
    string inputFile = "input.txt";
    string compressedFile = "compressed.bin";
    string decompressedFile = "decompressed.txt";

    unordered_map<char, int> freqMap;

    compressFile(inputFile, compressedFile, freqMap);

    // Rebuild tree for decompression
    Node *root = buildHuffmanTree(freqMap);

    decompressFile(compressedFile, decompressedFile, root);

    return 0;
}