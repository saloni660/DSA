#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// A Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Custom compare function for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string> &huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to build Huffman Tree and generate codes
Node* buildHuffmanTree(const unordered_map<char, int> &freqMap, unordered_map<char, string> &huffmanCode) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        Node *newNode = new Node('\0', sum);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();
    generateCodes(root, "", huffmanCode);
    return root;
}

// Function to encode the input string
string encode(const string &text, const unordered_map<char, string> &huffmanCode) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode.at(ch);
    }
    return encoded;
}

// MAIN FUNCTION
int main() {
    int n;
    unordered_map<char, int> freqMap;
    unordered_map<char, string> huffmanCode;

    cout << "Enter number of characters: ";
    cin >> n;
    cout << "Enter character and its frequency:\n";

    for (int i = 0; i < n; ++i) {
        char ch;
        int freq;
        cin >> ch >> freq;
        freqMap[ch] = freq;
    }

    Node* root = buildHuffmanTree(freqMap, huffmanCode);

    cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    string text;
    cout << "\nEnter a string to encode using above codes: ";
    cin >> text;

    string encoded = encode(text, huffmanCode);
    cout << "\nEncoded string: " << encoded << endl;

    return 0;
}
