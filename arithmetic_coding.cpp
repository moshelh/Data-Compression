#include <iostream>
#include "CreateFrequencyTable.cpp"
using namespace std;
void initFrequencyTable(){
    map<unsigned char, float> char_freqs = CreateFrequencyTable (path) ;
    for (auto pair: char_freqs) {
       pair.second = pair.second/counter;
    }
}



