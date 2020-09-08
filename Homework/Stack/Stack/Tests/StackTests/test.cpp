#include "pch.h"
#include "../../Stack.h"

TEST(PushTest, EmptyStack)
{
    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        testStack.push(i);
        EXPECT_EQ(i + 1, testStack.size());
        EXPECT_EQ(i, testStack.top());
    }
}

TEST(PushTest, PushAfterDelete)
{
    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        testStack.push(i);
        EXPECT_EQ(i + 1, testStack.size());
        EXPECT_EQ(i, testStack.top());
    }

    testStack.pop();
    testStack.pop();
    testStack.push(0);
    EXPECT_EQ(0, testStack.top());
}

TEST(PopTest, EmptyStack)
{
    stack<int> testStack;

    testStack.pop();
    EXPECT_EQ(0, testStack.size());
}

TEST(PopTest, NotEmpty)
{
    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        testStack.push(i);
        EXPECT_EQ(i + 1, testStack.size());
        EXPECT_EQ(i, testStack.top());
    }

    for (int i = 10; i > 0; --i)
    {
        EXPECT_EQ(i - 1, testStack.top());
        EXPECT_EQ(i, testStack.size());
        testStack.pop();
    }
}

TEST(TopTest, EmptyStack)
{
    stack<int> testStack;

    EXPECT_THROW(testStack.top(), std::out_of_range);
}

TEST(TopTest, NotEmpty)
{
    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        testStack.push(i);
        EXPECT_EQ(i + 1, testStack.size());
        EXPECT_EQ(i, testStack.top());
    }
}