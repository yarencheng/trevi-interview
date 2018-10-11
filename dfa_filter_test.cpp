#include "dfa_filter.hpp"

#include "gtest/gtest.h"

using namespace ::std;
using namespace ::testing;
using namespace ::interview;

TEST(DFAFilter, init_1) {

  // arrange
  DFAFilter filter;
  unordered_map<char, vector<string>> expected = {
    { 'a', {""} }
  };

  // action
  filter.init({"a"});
  unordered_map<char, vector<string>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, init_2) {

  // arrange
  DFAFilter filter;
  unordered_map<char, vector<string>> expected = {
    { 'a', {"bc"} }
  };

  // action
  filter.init({"abc"});
  unordered_map<char, vector<string>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, init_3) {

  // arrange
  DFAFilter filter;
  unordered_map<char, vector<string>> expected = {
    { 'a', {"bc"} },
    { 'd', {"ef"} }
  };

  // action
  filter.init({"abc","def"});
  unordered_map<char, vector<string>> actual = filter.getDFATree();


  // assert
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, init_4) {

  // arrange
  DFAFilter filter;
  unordered_map<char, vector<string>> expected = {
    { 'a', {"def", "bc"} }
  };

  // action
  filter.init({"abc","adef"});
  unordered_map<char, vector<string>> actual = filter.getDFATree();


  // assert
  // EXPECT_TRUE(actual==expected);
  EXPECT_EQ(actual, expected);
}

TEST(DFAFilter, filter_1) {

  // arrange
  DFAFilter filter;
  filter.init({"a"});

  // action
  string actual = filter.filter("abbbabbba");

  // assert
  EXPECT_EQ(actual, "*bbb*bbb*");

}

TEST(DFAFilter, filter_2) {

  // arrange
  DFAFilter filter;
  filter.init({"aa"});

  // action
  string actual = filter.filter("aabbbaabbbaa");

  // assert
  EXPECT_EQ(actual, "**bbb**bbb**");

}

TEST(DFAFilter, filter_3) {

  // arrange
  DFAFilter filter;
  filter.init({"aaa"});

  // action
  string actual = filter.filter("aaabbbaaabbbaaa");

  // assert
  EXPECT_EQ(actual, "***bbb***bbb***");

}

TEST(DFAFilter, filter_4) {

  // arrange
  DFAFilter filter;
  filter.init({"a", "ab", "abc", "abcd"});

  // action
  string actual = filter.filter("abcdefg");

  // assert
  EXPECT_EQ(actual, "****efg");

}

TEST(DFAFilter, filter_5) {

  // arrange
  DFAFilter filter;
  filter.init({"二"});

  // action
  string actual = filter.filter("一二三");

  // assert
  EXPECT_EQ(actual, "一**三");

}

