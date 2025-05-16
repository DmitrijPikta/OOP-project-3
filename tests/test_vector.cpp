#include "../src/Vector.h"
#include <gtest/gtest.h>

TEST(VectorTest, DefaultConstructor)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_GE(v.capacity(), 1);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, InitializerListConstructor)
{
    Vector<int> v{1, 2, 3};
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, CopyConstructor)
{
    Vector<std::string> v1{"a", "b"};
    Vector<std::string> v2(v1);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], "a");
    EXPECT_EQ(v2[1], "b");
    EXPECT_EQ(v1, v2);
}

TEST(VectorTest, MoveConstructor)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, CopyAssignment)
{
    Vector<int> v1{1, 2};
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v1, v2);
}

TEST(VectorTest, MoveAssignment)
{
    Vector<int> v1{4, 5, 6};
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 4);
    EXPECT_EQ(v2[1], 5);
    EXPECT_EQ(v2[2], 6);
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, PushBackAndPopBack)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 20);
    v.pop_back();
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.back(), 10);
}

TEST(VectorTest, InsertAndErase)
{
    Vector<int> v{1, 2, 4};
    v.insert(2, 3); // Insert 3 at index 2
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v.size(), 4);
    v.erase(1); // Remove element at index 1 (2)
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v.size(), 3);
}

TEST(VectorTest, Resize)
{
    Vector<int> v{1, 2};
    v.resize(5, 7);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[2], 7);
    v.resize(2);
    EXPECT_EQ(v.size(), 2);
}

TEST(VectorTest, ReserveAndShrinkToFit)
{
    Vector<int> v;
    v.reserve(10);
    EXPECT_GE(v.capacity(), 10);
    v.push_back(1);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorTest, AtThrowsOnInvalidIndex)
{
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v.at(-1), std::out_of_range);
    EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, FrontAndBack)
{
    Vector<int> v{5, 6, 7};
    EXPECT_EQ(v.front(), 5);
    EXPECT_EQ(v.back(), 7);
}

TEST(VectorTest, Assign)
{
    Vector<int> v{1, 2, 3};
    v.assign(4, 9);
    EXPECT_EQ(v.size(), 4);
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(v[i], 9);
}

TEST(VectorTest, EmplaceAndEmplaceBack)
{
    Vector<std::string> v{"a", "b"};
    v.emplace(1, 3, 'x'); // Insert "xxx" at index 1
    EXPECT_EQ(v[1], "xxx");
    v.emplace_back(2, 'y');
    EXPECT_EQ(v.back(), "yy");
}

TEST(VectorTest, ComparisonOperators)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{1, 2, 3};
    Vector<int> v3{1, 2, 4};
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 < v3);
    EXPECT_TRUE(v3 > v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v3 >= v2);
}

TEST(VectorTest, Swap)
{
    Vector<int> v1{1, 2};
    Vector<int> v2{3, 4, 5};
    v1.swap(v2);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, Clear)
{
    Vector<int> v{1, 2, 3};
    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

// Additional tests for full coverage

TEST(VectorTest, BeginEnd)
{
    Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
        sum += *it;
    EXPECT_EQ(sum, 6);

    const Vector<int> cv{4, 5};
    int sum2 = 0;
    for (auto it = cv.begin(); it != cv.end(); ++it)
        sum2 += *it;
    EXPECT_EQ(sum2, 9);
}

TEST(VectorTest, ConstFrontBack)
{
    const Vector<int> v{10, 20};
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 20);
}

TEST(VectorTest, ConstAtAndBracket)
{
    const Vector<int> v{7, 8, 9};
    EXPECT_EQ(v.at(1), 8);
    EXPECT_EQ(v[2], 9);
}

TEST(VectorTest, OperatorBracketThrows)
{
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v[-1], std::out_of_range);
    EXPECT_THROW(v[3], std::out_of_range);
}

TEST(VectorTest, EmplaceThrowsOnInvalidIndex)
{
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v.emplace(-1, 42), std::out_of_range);
    EXPECT_THROW(v.emplace(5, 42), std::out_of_range);
}

TEST(VectorTest, InsertThrowsOnInvalidIndex)
{
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v.insert(-1, 42), std::out_of_range);
    EXPECT_THROW(v.insert(5, 42), std::out_of_range);
}

TEST(VectorTest, EraseThrowsOnInvalidIndex)
{
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v.erase(-1), std::out_of_range);
    EXPECT_THROW(v.erase(3), std::out_of_range);
}

TEST(VectorTest, ResizeThrowsOnNegative)
{
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v.resize(-1), std::out_of_range);
}

TEST(VectorTest, Empty)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    EXPECT_FALSE(v.empty());
}

TEST(VectorTest, CapacityAfterReserveAndShrink)
{
    Vector<int> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100);
    v.push_back(1);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorTest, AssignLargerThanCapacity)
{
    Vector<int> v{1, 2};
    v.assign(10, 5);
    EXPECT_EQ(v.size(), 10);
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(v[i], 5);
}

TEST(VectorTest, EmplaceBackMany)
{
    Vector<std::string> v;
    v.emplace_back("abc");
    v.emplace_back(3, 'z');
    EXPECT_EQ(v[0], "abc");
    EXPECT_EQ(v[1], "zzz");
}

TEST(VectorTest, SwapSelf)
{
    Vector<int> v{1, 2, 3};
    v.swap(v);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, SelfAssignment)
{
    Vector<int> v{1, 2, 3};
    v = v;
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, SelfMoveAssignment)
{
    Vector<int> v{1, 2, 3};
    v = std::move(v);
    EXPECT_EQ(v.size(), 3); // Should remain valid
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
