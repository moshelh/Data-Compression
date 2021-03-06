#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <chrono>
#include "CreateFrequencyTable.cpp"
std::string decodeString="";
std::string path="/home/moshe/CLionProjects/Final-Project/Document/binarySearch.out";
using namespace std;
struct Node
{
    unsigned char ch;
    int freq;
    Node *left, *right;
};
Node* root;
struct comp
{
    bool operator()(Node* l, Node* r)
    {
        // highest priority item has lowest frequency
        return l->freq > r->freq;
    }
};

Node* getNode(unsigned char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}
void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (!root->left && !root->right)
    {
        decodeString+=root->ch;
        return;
    }

    index++;

    if (str[index] =='0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}
void encode(Node* root, string str,
            unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
std::map <unsigned char, int> createFrequencyTable (const std::string &strFile)
{
    std::map <unsigned char, int> char_freqs ; // character frequencies

    std::ifstream file (strFile,std::ios::binary) ;
    int next = 0 ;
    while ((next = file.get ()) != EOF) {
        unsigned char uc = static_cast <unsigned char> (next) ;

        std::map <unsigned char, int>::iterator iter ;
        iter = char_freqs.find (uc) ;

        // This character is in our map.
        if (iter != char_freqs.end ()) {
            iter->second += 1 ;
        }

            // This character is not in our map yet.
        else {
            char_freqs [uc] = 1 ;
        }

    }

    return char_freqs ;
}
basic_string<char> buildHuffmanTree()
{
    // count frequency of appearance of each character
    // and store it in a map

    std::map <unsigned char, int> char_freqs = createFrequencyTable (path) ;


    // Create a priority queue to store live nodes of
    // Huffman tree;
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create a leaf node for each character and add it
    // to the priority queue.
    for (auto pair: char_freqs) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        // Remove the two nodes of highest priority
        // (lowest frequency) from the queue
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top();	pq.pop();

        // Create a new internal node with these two nodes
        // as children and with frequency equal to the sum
        // of the two nodes' frequencies. Add the new node
        // to the priority queue.
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // root stores pointer to root of Huffman Tree
    root = pq.top();

    // traverse the Huffman Tree and store Huffman Codes
    // in a map. Also prints them
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n" << '\n';
//    for (auto pair: huffmanCode) {
//        std::string binary = std::bitset<8>(pair.first).to_string();
//        cout << binary << " :: " << pair.second << '\n';
//    }

    int next1 = 0 ;
    std::ifstream file (path,std::ios::binary) ;
    string binString ="";
    while ((next1 = file.get ()) != EOF){
        std::string binary = std::bitset<8>(next1).to_string();
        binString += binary;
    }
    std::ifstream file1 (path,std::ios::binary) ;
    int next = 0 ;
    string str="";
    while ((next = file1.get ()) != EOF){
        str+=huffmanCode[next];
    }

    return str;
}
void decodeHuffman(string str) {
    // traverse the Huffman Tree again and this time
    // decode the encoded string
    int index = -1;
    cout << "\nDecoded string is: \n";
    while (index < (int)str.size() - 2) {
        decode(root, index, str);
    }
    cout << decodeString.length() << endl;
    std::ofstream out("/home/moshe/CLionProjects/Final-Project/Output/output.out");
    out << decodeString;
    out.close();
}


int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::string str=buildHuffmanTree();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout<<"first: " << duration;

    t1 = std::chrono::high_resolution_clock::now();
    decodeHuffman(str);
    t2 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout<<"second : " << duration;
    return 0;
}


