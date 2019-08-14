// readingfromfilewithblanks.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include <algorithm>
#include "ArgumentManager.h"


using namespace std;
void stringToVector(vector<string> &field, string astring, string anotherstring);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Figure this out later";
		return 1;
	}
	ArgumentManager  am(argc, argv);
	string filename = am.get("input");
	string outfile = am.get("output");
	// Open file
	cout << "Opening file myfile.txt." << endl;
	ifstream inFS(filename.c_str());   // Input file stream
	char line = ' '; // File data
	vector<char> Stringy(0);
	string s;

	if (!inFS.is_open()) {
		cout << "Could not open file myfile.txt." << argv[1]<< endl;
		return 1;
	}

	// Print read numbers to output
	cout << "Reading and printing numbers." << endl;

	while (!inFS.eof()) {
		inFS >> line;
		if (inFS.good()) {
			//cout <<  line << endl;
			Stringy.push_back(line);
		}
	}
	cout << endl << endl << endl;
	cout << "Heres where I make it into a string";
	string str(Stringy.begin(), Stringy.end());
	string partial = " ";
	cout << endl << endl << endl;
	cout << str;
	cout << endl << endl << endl;
	vector<string> field(0);
	stringToVector(field, str, partial);
	std::sort(field.begin(), field.end());
	field.erase(std::unique(field.begin(), field.end()), field.end());
	cout << "Closing file myfile.txt." << argv[1]<< endl;

	// Done with file, so close it
	inFS.close();
	cout << endl << endl << endl;

	for (int i = 0; i < field.size(); i++) {
		cout << field.at(i) << endl;
	}
	cout << endl << endl << endl;
	ofstream outFS; // Output file stream

					// Open file
	outFS.open(outfile);

	if (!outFS.is_open()) {
		cout << "Could not open file myoutfile.txt." << endl;
		return 1;
	}
	for (vector<string>::const_iterator i = field.begin(); i != field.end(); ++i) {
		outFS << *i << '\n';
	}
	outFS.close();
	system("pause");
	return 0;
}

void stringToVector(vector<string> &field, string astring, string anotherstring) {
	while (astring.find('}') != string::npos) {
		anotherstring = astring.substr(0, astring.find('}') + 1);
		field.push_back(anotherstring);
		astring = astring.substr(astring.find('}') + 1);
	}
	field.push_back(astring);
}