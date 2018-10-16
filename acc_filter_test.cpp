#include "acc_filter.hpp"

#include "gtest/gtest.h"

using namespace ::std;
using namespace ::testing;
using namespace ::interview;

typedef unordered_map<wchar_t, shared_ptr<ACCNode>> CHILDS_T;

TEST(ACCFilter, add_empty) {

  // arrange
  ACCFilter filter;
  auto expected = make_shared<ACCNode>();

  // assert
  auto actual = filter.getRoot();
  EXPECT_EQ(*expected, *actual);
}

TEST(ACCFilter, add_oneDirtyWord) {

  // arrange
  ACCFilter filter;
  auto expected = make_shared<ACCNode>(
    CHILDS_T({{L'a', make_shared<ACCNode>()}})
  );

  // action
  filter.add(L"a");

  // assert
  auto actual = filter.getRoot();
  EXPECT_EQ(*expected, *actual);
}

TEST(ACCFilter, add_twoDirtyWord_1) {

  // arrange
  ACCFilter filter;
  auto expected = make_shared<ACCNode>(
    CHILDS_T({
      {L'a', make_shared<ACCNode>()},
      {L'b', make_shared<ACCNode>()}
    })
  );

  // action
  filter.add(L"a");
  filter.add(L"b");

  // assert
  auto actual = filter.getRoot();
  EXPECT_EQ(*expected, *actual);
}

TEST(ACCFilter, add_twoDirtyWord_2) {

  // arrange
  ACCFilter filter;
  auto expected = make_shared<ACCNode>(
    CHILDS_T({
      {L'a', make_shared<ACCNode>(
        CHILDS_T({
          {L'a', make_shared<ACCNode>()},
          {L'b', make_shared<ACCNode>()}
        })
      )}
    })
  );

  // action
  filter.add(L"aa");
  filter.add(L"ab");

  // assert
  auto actual = filter.getRoot();
  EXPECT_EQ(*expected, *actual);
}

TEST(ACCFilter, add_twoDirtyWord_3) {

  // arrange
  ACCFilter filter;
  auto expected = make_shared<ACCNode>(
    CHILDS_T({
      {L'a', make_shared<ACCNode>(
        CHILDS_T({
          {L'a', make_shared<ACCNode>()}
        })
      )},
      {L'b', make_shared<ACCNode>(
        CHILDS_T({
          {L'b', make_shared<ACCNode>()}
        })
      )}
    })
  );

  // action
  filter.add(L"aa");
  filter.add(L"bb");

  // assert
  auto actual = filter.getRoot();
  EXPECT_EQ(*expected, *actual);
}