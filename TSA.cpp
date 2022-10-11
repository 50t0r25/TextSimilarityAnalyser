#include <iomanip>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values
#define MAX(x,y) ((x) > (y) ? (x) : (y)) //calculate maxiumum between two values

using namespace std;

//takes filename as input and returns content as a string
string fileToString(const char* fileName) {
    ifstream ifs(fileName, ios::in | ios::binary | ios::ate);

    size_t fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    std::vector<char> data;
    data.reserve(fileSize);
    ifs.read(data.data(), fileSize);
    
    std::string str(data.data());
    return str;
}

string toLowerCase(string str) {
    for (int x=0; x < str.length(); x++)
        str[x] = tolower(str[x]);
    return str;
}

int main(int argc, char *argv[]) {

    int i,j,l1,l2,t,track;

    string s1 ,s2;

    //read files and dump content to s1 and s2
    try {
        s1 = toLowerCase(fileToString(argv[1]));
        s2 = toLowerCase(fileToString(argv[2]));
    } catch(...) {
        cout << "File not found, please retry.\n";
        return 0;
    }

    //stores the lenght of strings s1 and s2
    l1 = s1.length();
    l2 = s2.length();

    std::vector<std::vector<int>> dist(l2+1,std::vector<int>(l1+1,0));

    //initialize arrays
    for(i=0;i<=l1;i++) {
        dist[0][i] = i;
    }
    for(j=0;j<=l2;j++) {
        dist[j][0] = j;
    }

    //start looping
    for (j=1;j<=l1;j++) {
        for(i=1;i<=l2;i++) {

            //calculate cost
            if(s1[i-1] == s2[j-1]) {
                track= 0;
            } else {
                track = 1;
            }
            t = MIN((dist[i-1][j]+1),(dist[i][j-1]+1));
            dist[i][j] = MIN(t,(dist[i-1][j-1]+track));
        }
    }

    //number of edits required AKA Levenshtein Distance
    int edits = dist[l2][l1];

    //percentage from Levenshtein Distance
    float s_percentage = 100.0 - ((static_cast< float >(edits))/static_cast< float >(MAX(l1,l2)-1))*100;
    if (s_percentage<0) s_percentage = 0;

    cout << setprecision (2) << fixed << "Similarity is: " << s_percentage << "%\n";

    return 0;
}