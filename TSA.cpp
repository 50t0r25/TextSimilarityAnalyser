#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values
#define MAX(x,y) ((x) > (y) ? (x) : (y)) //calculate maxiumum between two values

//takes filename as input and returns content as a string
std::string fileToString(const char* fileName) {
    ifstream ifs(fileName, ios::in | ios::binary | ios::ate);

    size_t fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    std::vector<char> data;
    data.reserve(fileSize);
    ifs.read(data.data(), fileSize);
    
    std::string str(data.data());
    return str;
}


int main(int argc, char* argv[]) {

    std::string file1 = fileToString(argv[1]);
    std::string file2 = fileToString(argv[2]);

    //stores the lenght of strings s1 and s2
    size_t l1 = file1.length();
    size_t l2 = file2.length();

    std::vector<std::vector<int>> dist(l2+1,std::vector<int>(l1+1,0));

    int track,t;
    //start looping
    for (int j=1; j<=l1 ; j++) {
        for(int i=1; i<=l2 ; i++) {

            //calculate cost
            if(file1[j-1] == file2[i-1]) {
                track= 0;
            } else {
                track = 1;
            }
            t = MIN((dist[i-1][j]+1),(dist[i][j-1]+1));
            dist[i][j] = MIN(t,(dist[i-1][j-1]+track));
        }
    }
    
    //number of edits required AKA Levenshtein Distance
    int edits = dist[l2-1][l1-1];

    //percentage from Levenshtein Distance
    float s_percentage = 100.0 - ((static_cast<float>(edits)) / static_cast<float>(MAX(l1,l2)-1))*100;
    if (s_percentage<0) s_percentage = 0;

    cout << setprecision (2) << fixed << "Similarity is: " << s_percentage << "%\n" << std::endl;

    return 0;
}