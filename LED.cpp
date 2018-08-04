#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "const.h"

using namespace std;

class LED {
  public:  
    LED (string fileName) {
      file.open(fileName.c_str());
      if (!file.good()) {
        throw invalid_argument( "File not found!" );
      }
    }
    
    vector<int> GetAllNumbers() {
      vector<string> lines = this->readFromFile();
      vector<int> result = this->convertToNumber(lines);
      return result;
    }
  
  protected:
    ifstream file;
    
    vector<string> readFromFile() {
      vector<string> result;
      string str;
      
      while (getline(file, str, '\n')) {
        result.push_back(str);
      }
      
      return result;
    }
    
    vector<int> convertToNumber(const vector<string> &lines) {
      vector<int> result;
      for (int i = 0; i < lines[0].size(); i += 4) {
        int choosen  = -1;
        for (int number = 0; number <= 9; number++) {
          bool perfect = true;
          for (int j = 0; j < 3 && perfect; j++) {
            for (int k = 0; k < 3 && perfect; k++) {
              if (lines[j][i + k] != GUIDE[j][number * 3 + number + k]) {
                perfect = false;
              }  
            }
          }
          if (perfect) {
            choosen = number;
            break;
          }
        }
        result.push_back(choosen);
      }
      return result;
    }
    
    ~LED() {
      file.close();
    }
};
