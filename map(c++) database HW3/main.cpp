//#include "stdafx.h"
#include"ArgumentManager.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<set>
#include<map>
#include<algorithm>
#include<utility>
#include<iterator>
using namespace std;
string cleanLine(string var);


int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Figure this out later";
        return 1;
    }
    ArgumentManager  am(argc, argv);
    string filename = am.get("input");
    string outfile = am.get("output");
    ifstream inFS(filename.c_str());
    set<unsigned long long> set1;
    set<unsigned long long> set2;

    unordered_map<string, set<unsigned long long>> var;
    ofstream vout;
    //ifstream inFS;   // Input file stream
    char fileNum = 0; // File data
    ifstream inFS2;
    char fileNum2 = 0;
    string instruction;
    string partial;
    string val2Find;
    string line2Read;
    vector<string> myString;
    vector<char> Stringy;
    vector<string> myString2;
    vector<string>field;
    vector<string>field2;
    //ifstream inFile;
    string word;

    //inFile.open(filename);
    int i = 0;
    // Open file
    map<unsigned long long, vector<string>>Rec_id;
    unsigned long long line_count = 0;
    vector<string> var2;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Could not open file myfile.txt." << endl;
        return 1;
    }

    // Print read numbers to output

    ofstream outFS(outfile);
    if (inFile.is_open()) {

        cout << "test" << endl;
        //Read until no more lines in text file to read


        while (inFile >> instruction >> line2Read) {

            if (instruction == "add") {

                istringstream obj(cleanLine(line2Read));
                var2.clear();
                while (obj >> word) {
                    var2.push_back(word);
                    var[word].insert(line_count);

                }
                Rec_id[line_count] = var2;
                line_count++;
            }
            else if (instruction == "get") {
		auto x = cleanLine(line2Read);
                istringstream obj2(cleanLine(line2Read));
                obj2>>word;
                auto set1= var[word];
                while (obj2 >> word) {
                    set<unsigned long long> intersection;
                    auto set2 = var[word];
                    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
                    set1 = intersection;
                    if (set1.empty()) {
                        break;
                    }

                }
                for (auto id : set1) {
                    outFS << "{";
                    auto& record1 = Rec_id[id];
                    int counter = 0;
                    for (auto& valu : record1) {
                        counter++;
                        outFS << valu ;
                        if (counter != record1.size()) {
                            outFS << ",";
                        }
                    }
                    outFS << "}";
                    outFS << endl;
                }
                outFS<<endl;


            }
            else if (instruction == "delete") {
                auto x = cleanLine(line2Read);
                istringstream obj2(cleanLine(line2Read));
                obj2>>word;
                auto set1= var[word];
                while (obj2 >> word) {
                    set<unsigned long long> intersection;
                    auto set2 = var[word];
                    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
                    set1 = intersection;
                    if (set1.empty()) {
                        break;
                    }

                }
                for (auto id : set1) {
                    auto& fecvar = Rec_id[id];
                    for (auto attFound : fecvar) {
                        var[attFound].erase(id);
                    }
                }
            }
            else


                continue;

        }
    }
    /*
    for (auto ils : intersection) {
        auto&find = Rec_id[ils];
        for (auto & word : intersection) {
            cout << word << " ";
        }
    }
    */

/*
	for (int i = 0; i < myString.size()-1; i++)
	{
		set<unsigned long long> intersection;
		set1 =var[myString.at(i)];
		set2= var[myString.at(i+1)];
		set_intersection(set1.begin(),set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
		set1 = intersection;
		if (set1.empty()) {
			cout << "Set1 is empty" << endl;
			break;
		}
	}

	*/





    /*
         for (auto entry : var) {
        std::cout << entry.first << " :: ";
        for (int i : entry.second)
            std::cout << i << " , ";
        std::cout << std::endl;
    }

     */
    map<unsigned long long, vector<string>> aVar;




    
    return 0;
}

string cleanLine(string var ){
    //string str;
    for (int i = 0; i < var.length(); i++) {
        if (var.at(i) == '{' || var.at(i) == ',' || var.at(i) == '}')

            var.at(i) = ' ';
        //str += var;

    }
    return var;
};
