#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cinttypes>

using namespace std;

vector<string> getFileInput(ifstream &fileIn) {
  string str;
  vector<string> vecofstrs;

  while (getline(fileIn, str))
  {
  	if(str.size() > 0) {
      int resultpos = str.size()-1;
      if (str[resultpos] == '1') { //determining whether or not result of that line is 1.
        vecofstrs.push_back(str);
        str.clear();
      }

    }
  }

  sort(vecofstrs.begin(), vecofstrs.end()); //sort in ascending order.

  vector<string> input_only; //now start stripping outputs.

  for (int i=0; i<vecofstrs.size(); i++) {
    string line = vecofstrs[i];
    string inputs;
    for (int j=0; j<line.size(); j++) {
      if (line[j] != '|') {
        inputs.push_back(line[j]);
      } else {
        input_only.push_back(inputs);
        inputs.clear();
        j+=1;
      }
    }
  }

  return input_only;
}


int main(int argc, char* argv[]) {

  //take in file 1
  string file1 = argv[1];
  ifstream inStream1(file1);
  vector<string> file1_content = getFileInput(inStream1);

  //take in file 2.
  string file2 = argv[2];
  ifstream inStream2(file2);
  vector<string> file2_content = getFileInput(inStream2);

  //compare the size of the the 2 files, and add trailing zeroes if necessary.
  int file1_width = file1_content[0].size();
  int file2_width = file2_content[0].size();
  vector<string> file1_mod;
  vector<string> file2_mod;
  if (file1_width < file2_width) {
    file2_mod = file2_content;
    int diff = file2_width-file1_width;
    for (int i=0; i<file1_content.size(); i++) {
      string line = file1_content[i];
      for (int j=0; j<diff; j++) {
        line = line + '0';
        file1_mod.push_back(line);
      }
    }
  } else if (file2_width < file1_width) {
    file1_mod = file1_content;
    int diff = file1_width-file2_width;
    for (int i=0; i<file2_content.size(); i++) {
      string line = file2_content[i];
      for (int j=0; j<diff; j++) {
        line = line + '0';
        file2_mod.push_back(line);
      }
    }
  } else {
    file1_mod = file1_content;
    file2_mod = file2_content;
  }

  //combine the 2 vectors and sort in order.
  vector<string> combined;
  for (int i=0; i<file1_mod.size(); i++) {
    combined.push_back(file1_mod[i]);
  }
  for (int j=0; j<file2_mod.size(); j++) {
    combined.push_back(file2_mod[j]);
  }
  sort(combined.begin(),combined.end());

  //start comparing and outputting differences
  bool equivalent = true;
  for (int k=0; k<combined.size(); k++) {
    if (combined[k] == combined [k+1]) {
      k+=1;
    } else {
      equivalent = false;
      cout << combined[k] << endl;
      if (combined[k+1] == combined[k+2]) {
        k+=2;
      } else {
        cout << combined[k+1] << endl;
        k+=1;
      }
    }
  }
  if (equivalent == true) {
    return 0;
  } else {
    return 1;
  }

}
