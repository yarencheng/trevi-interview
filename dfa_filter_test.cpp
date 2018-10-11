#include "dfa_filter.hpp"

#include "gtest/gtest.h"

using namespace ::std;
using namespace ::testing;
using namespace ::interview;

TEST(DFAFilter, add_1) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L""} }
  };

  // action
  filter.add({L"a"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, add_2) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"bc"} }
  };

  // action
  filter.add({L"abc"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, add_3) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"bc"} },
    { 'd', {L"ef"} }
  };

  // action
  filter.add({L"abc",L"def"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, add_4) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"def", L"bc"} }
  };

  // action
  filter.add({L"abc",L"adef"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, add_5) {

  // arrange
  DFAFilter filter;
  unordered_map<wchar_t, vector<wstring>> expected = {
    { 'a', {L"bc"} }
  };

  // action
  filter.add({L"abc"});
  filter.add({L"abc"});
  unordered_map<wchar_t, vector<wstring>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, filter_1) {

  // arrange
  DFAFilter filter;
  filter.add({L"a"});

  // action
  wstring actual = filter.filter(L"abbbabbba");

  // assert
  EXPECT_EQ(actual, L"*bbb*bbb*");

}

TEST(DFAFilter, filter_2) {

  // arrange
  DFAFilter filter;
  filter.add({L"aa"});

  // action
  wstring actual = filter.filter(L"aabbbaabbbaa");

  // assert
  EXPECT_EQ(actual, L"**bbb**bbb**");

}

TEST(DFAFilter, filter_3) {

  // arrange
  DFAFilter filter;
  filter.add({L"aaa"});

  // action
  wstring actual = filter.filter(L"aaabbbaaabbbaaa");

  // assert
  EXPECT_EQ(actual, L"***bbb***bbb***");

}

TEST(DFAFilter, filter_4) {

  // arrange
  DFAFilter filter;
  filter.add({L"a", L"ab", L"abc", L"abcd"});

  // action
  wstring actual = filter.filter(L"abcdefg");

  // assert
  EXPECT_EQ(actual, L"****efg");

}

TEST(DFAFilter, filter_5) {

  // arrange
  DFAFilter filter;
  filter.add({L"二"});

  // action
  wstring actual = filter.filter(L"一二三");

  // assert
  EXPECT_EQ(actual, L"一*三");

}

