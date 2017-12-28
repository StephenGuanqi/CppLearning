//
// Created by Guanqi Yu on 12/17/17.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct PersonInfo {
	string name;
	vector<string> phones;
};

/**
 * stream is changing, can't declared as const
 */
istream &func(istream &is) {
	string buf;
	while (is >> buf) {
		cout << buf << endl;
	}
	is.clear();
	return is;
}

void ReadFileToVec(const string &fileName, vector<string> &vec) {
	ifstream ifs(fileName);
	if (ifs) {
		string buf;
		while (getline(ifs, buf))
			vec.push_back(buf);
	}
}

int main() {
	vector<string> vec;
	ReadFileToVec("../data/book.txt", vec);
	for (const auto &str : vec) {
		istringstream iss(str);
		string word;
		while (iss >> word) {
			cout << word << endl;
		}
	}


	string line, word;
	vector<PersonInfo> people;
	istringstream record;
	while (getline(cin, line))
	{
		PersonInfo info;
		record.clear(); // important because the while below set flags on the stream when end
		record.str(line);
		record >> info.name;
		while (record >> word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	// or remove record inside the while loop
}