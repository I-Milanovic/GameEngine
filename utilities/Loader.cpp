#include "Loader.h"
using namespace std;

	char* Loader::read(string fileName) {

		string myText;
		//char* myText;
		// Read from the text file
		ifstream MyReadFile(fileName);

		ostringstream ss;

		if (MyReadFile) {
			ss << MyReadFile.rdbuf();
			myText = ss.str();
		}
		else {
			cout << "File : " << "'" << fileName << "'" << " not found!" << endl;
		}

		// Close the file
		MyReadFile.close();

		int len =  myText.length();
		char* c = new char[len+1];

		myText.copy(c, len);

		c[len] = '\0';

		return c;
	}
