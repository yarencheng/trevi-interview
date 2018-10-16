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

TEST(ACCFilter, build) {

  // arrange
  ACCFilter filter;
  auto expected = make_shared<ACCNode>(
    0,
    0,
    CHILDS_T({
      {L's', make_shared<ACCNode>(
        2,
        0,
        CHILDS_T({
          {L'h', make_shared<ACCNode>(
            5,
            1,
            CHILDS_T({
              {L'e', make_shared<ACCNode>(
                8,
                3
              )}
            })
          )}
        })
      )},
      {L'h', make_shared<ACCNode>(
        1,
        0,
        CHILDS_T({
          {L'i', make_shared<ACCNode>(
            4,
            0,
            CHILDS_T({
              {L's', make_shared<ACCNode>(
                7,
                2
              )}
            })
          )},
          {L'e', make_shared<ACCNode>(
            3,
            0,
            CHILDS_T({
              {L'r', make_shared<ACCNode>(
                6,
                0,
                CHILDS_T({
                  {L's', make_shared<ACCNode>(
                    9,
                    2
                  )}
                })
              )}
            })
          )}
        })
      )}
    })
  );

  // action
  filter.add(L"she");
  filter.add(L"his");
  filter.add(L"hers");
  filter.add(L"he");
  filter.build();

  // assert
  auto actual = filter.getRoot();
  EXPECT_EQ(*expected, *actual);
}