#include <iostream>
#include <string>
#include "LED.cpp"

using namespace std;

int main() {
  string fileName;
  
  cin >> fileName;
  
  LED *led = new LED(fileName);
  vector<int> result = led->GetAllNumbers();
  
  for (int i = 0; i < result.size(); i++) {
    cout << result[i];
  }
  cout << endl;
  
  return 0;
}
