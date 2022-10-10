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

//calculates Levenshtein Distance between 2 strings and returns the number of edits requires
unsigned int edit_distance(const std::string& s1, const std::string& s2)
{
	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
                      d[i][j] = std::min(std::min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
	return d[len1][len2];
}


int main(int argc, char *argv[]) {

    int i,j,l1,l2,t,track;

    string f1, f2, s1 ,s2;

    //read files and dump content to s1 and s2
    try {
        f1 = argv[1];
        f2 = argv[2];

        s1 = fileToString(f1);
        s2 = fileToString(f2);
    } catch(...) {
        cout << "File not found, please retry.\n";
        return 0;
    }

    //number of edits required AKA Levenshtein Distance
    int edits = edit_distance(s1,s2);

    //percentage from Levenshtein Distance
    float s_percentage = 100.0 - ((static_cast< float >(edits))/static_cast< float >(MAX(l1,l2)-1))*100;

    cout << setprecision (2) << fixed << "Similarity is: " << s_percentage << "%\n";

    return 0;
}