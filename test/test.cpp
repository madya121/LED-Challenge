#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "../LED.cpp"

using namespace std;

class Test {
  public:
    Test() {}
    
    void RunTest(string fileName, const int expected[], int size) {
      MockLED *mock = new MockLED(fileName);
      
      vector<int> expectedResult(expected, expected + size);
      vector<int> result = mock->GetNumbers();
      
      assert(expectedResult.size() == result.size());
      
      for (int i = 0; i < expectedResult.size(); i++) {
        assert(expectedResult[i] == result[i]);
      }
      
      delete mock;
    }
    
    void TestFromFile(string fileName, const string expected[], int size) {
      MockLED *mock = new MockLED(fileName);
      
      vector<string> expectedResult(expected, expected + size);
      vector<string> result = mock->ReadFromFile();
      
      assert(expectedResult.size() == result.size());
      
      for (int i = 0; i < expectedResult.size(); i++) {
        assert(expectedResult[i] == result[i]);
      }
      
      delete mock;
    }
    
  private:
    class MockLED : protected LED {
      public:
        MockLED(string fileName) : LED(fileName) {}
        
        vector<string> ReadFromFile() {
          return this->readFromFile();
        }
        
        vector<int> ConvertToNumber(const vector<string> &lines) {
          return this->convertToNumber(lines);
        }
        
        vector<int> GetNumbers() {
          return this->GetAllNumbers();
        }
    };
};

int main() {
  Test *test = new Test();
  
  int expected1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  test->RunTest("test1.txt", expected1, sizeof(expected1) / sizeof(int));
  
  int expected2[] = {2, 1, 1, 1, 3, 5, 9, 8, 0, 1, 4, 8, 6, 2};
  test->RunTest("test2.txt", expected2, sizeof(expected2) / sizeof(int));
  
  int expected3[] = {4, 4, 1, 0};
  test->RunTest("test3.txt", expected3, sizeof(expected3) / sizeof(int));
  
  int expected4[] = {};
  test->RunTest("test4.txt", expected4, sizeof(expected4) / sizeof(int));
  
  string expected5[] = {"test1", "test2", "test3"};
  test->TestFromFile("test5.txt", expected5, sizeof(expected5) / sizeof(expected5[0]));
  
  return 0;
}
