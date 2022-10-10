#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;
#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values
#define MAX(x,y) ((x) > (y) ? (x) : (y)) //calculate maxiumum between two values

//takes filename as input and returns content as a string
string fileToString(const string &fileName) {
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(&bytes[0], fileSize);

    return string(&bytes[0], fileSize);
}


int main(int argc, char *argv[]) {

    int i,j,l1,l2,t,track;

    string f1 = argv[1], f2 = argv[2], s1 ,s2;

    //read files and dump content to s1 and s2
    try {
        s1 = fileToString(f1);
        s2 = fileToString(f2);
    } catch(...) {
        cout << "File not found, please retry.\n";
        return 0;
    }

    //stores the lenght of strings s1 and s2
    l1 = s1.length();
    l2= s2.length();

    int dist[l1+l2][l1+l2];

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