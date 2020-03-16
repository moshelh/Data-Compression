#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;
std::string path="/home/moshe/CLionProjects/Final-Project/Document/binarySearch.out";
int static counter=0;
std::map <unsigned char, float> CreateFrequencyTable (const std::string &strFile)
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
        counter++;
    }

    return char_freqs ;
}
