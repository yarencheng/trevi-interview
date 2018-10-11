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

class ProfilerTest : public TestWithParam<int> {
public:

};

INSTANTIATE_TEST_CASE_P(AnotherInstantiationName, ProfilerTest,
  ::testing::ValuesIn([]() -> vector<int> {
    int cur = 1000;
    vector<int> ans;
    while(cur<=200000){
      ans.push_back(cur);
      cur+=1000;
    }
    return ans;
  }()),
  testing::PrintToStringParamName()
);

TEST_P(ProfilerTest, add) {
  int dataSize = GetParam();

  DFAFilter filter;
  vector<wstring> words;

  while (dataSize-->0) {
    words.push_back(randomString(10));
  }

  filter.add(words);
}



