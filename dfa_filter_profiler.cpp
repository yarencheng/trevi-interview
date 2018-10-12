#include "dfa_filter.hpp"

#include "gtest/gtest.h"
#include <sstream>

using namespace ::std;
using namespace ::testing;
using namespace ::interview;

wstring randomString(int length) {
  static const wchar_t alphanum[] =
    L"0123456789"
    L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    L"abcdefghijklmnopqrstuvwxyz";

  wstringstream ss;

  for (int i = 0; i < length; ++i) {
    ss << alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return ss.str();
}

class Profiler : public TestWithParam<int> {
public:

};

INSTANTIATE_TEST_CASE_P(Profiler, Profiler,
  ::testing::ValuesIn([]() -> vector<int> {

    int min = stoi(getenv("DATASIZE_MIN"));
    int max = stoi(getenv("DATASIZE_MAX"));
    int step = stoi(getenv("DATASIZE_STEP"));

    int cur = min;
    vector<int> ans;
    while(cur<=max){
      ans.push_back(cur);
      cur+=step;
    }
    return ans;
  }()),
  testing::PrintToStringParamName()
);

TEST_P(Profiler, test) {
  int dataSize = GetParam();

  DFAFilter filter;
  vector<wstring> words;

  while (dataSize-->0) {
    words.push_back(randomString(10));
  }

  filter.add(words);
}



