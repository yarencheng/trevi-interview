#include "dfa_filter.hpp"

#include "gtest/gtest.h"

using namespace ::std;
using namespace ::testing;
using namespace ::interview;

TEST(DFAFilter, init_1) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L""} }
  };

  // action
  filter.init({L"a"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, init_2) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"bc"} }
  };

  // action
  filter.init({L"abc"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, init_3) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"bc"} },
    { 'd', {L"ef"} }
  };

  // action
  filter.init({L"abc",L"def"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, init_4) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"def", L"bc"} }
  };

  // action
  filter.init({L"abc",L"adef"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, filter_1) {

  // arrange
  DFAFilter filter;
  filter.init({L"a"});

  // action
  wstring actual = filter.filter(L"abbbabbba");

  // assert
  EXPECT_EQ(actual, L"*bbb*bbb*");

}

TEST(DFAFilter, filter_2) {

  // arrange
  DFAFilter filter;
  filter.init({L"aa"});

  // action
  wstring actual = filter.filter(L"aabbbaabbbaa");

  // assert
  EXPECT_EQ(actual, L"**bbb**bbb**");

}

TEST(DFAFilter, filter_3) {

  // arrange
  DFAFilter filter;
  filter.init({L"aaa"});

  // action
  wstring actual = filter.filter(L"aaabbbaaabbbaaa");

  // assert
  EXPECT_EQ(actual, L"***bbb***bbb***");

}

TEST(DFAFilter, filter_4) {

  // arrange
  DFAFilter filter;
  filter.init({L"a", L"ab", L"abc", L"abcd"});

  // action
  wstring actual = filter.filter(L"abcdefg");

  // assert
  EXPECT_EQ(actual, L"****efg");

}

TEST(DFAFilter, filter_5) {

  // arrange
  DFAFilter filter;
  filter.init({L"二"});

  // action
  wstring actual = filter.filter(L"一二三");

  // assert
  EXPECT_EQ(actual, L"一*三");

}

