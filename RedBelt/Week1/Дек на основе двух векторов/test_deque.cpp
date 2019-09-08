#pragma once
#include "test_runner.h"
#include "deque_via_two_vectors.cpp"
#include <deque>
#include <iostream>

using namespace std;

void DequeTests()
{

    Deque<int> deque;
    ASSERT(deque.Empty());
    ASSERT_EQUAL(deque.Size(), 0);

    deque.PushBack(1);
    ASSERT(!deque.Empty());
    ASSERT_EQUAL(deque.Size(), 1);
    {
        int a = deque[0];
        int b = deque.At(0);

        ASSERT_EQUAL(a, 1);
        ASSERT_EQUAL(b, 1);
        ASSERT_EQUAL(deque.Back(), 1);
    }

    deque.PushFront(2);
    ASSERT_EQUAL(deque.Size(), 2);
    {
        int a = deque[0];
        int a_at = deque.At(0);
        int b = deque[1];
        int b_at = deque.At(1);


        ASSERT_EQUAL(a, 2);
        ASSERT_EQUAL(a_at, 2);
        ASSERT_EQUAL(b, 1);
        ASSERT_EQUAL(b_at, 1);
        ASSERT_EQUAL(deque.Back(), 1);
        ASSERT_EQUAL(deque.Front(), 2);
    }
    deque.PushFront(3);
    {

        int a = deque[0];
        int a_at = deque.At(0);

        ASSERT_EQUAL(a, 3);
        ASSERT_EQUAL(a_at, 3);
        ASSERT_EQUAL(deque[1], 2);
        ASSERT_EQUAL(deque.At(1), 2);
        ASSERT_EQUAL(deque[2], 1);
        ASSERT_EQUAL(deque.At(2), 1);
        ASSERT_EQUAL(deque.Back(), 1);
        ASSERT_EQUAL(deque.Front(), 3);
    }


    {
        Deque<int> deque;
        deque.PushFront(1);
        ASSERT_EQUAL(deque[0],1);
        ASSERT_EQUAL(deque.Back(),deque.Front());
        deque.PushFront(2);
        deque.PushFront(3);
        ASSERT_EQUAL(deque.Size(), 3);
        ASSERT_EQUAL(deque[0],3);
        ASSERT_EQUAL(deque[1],2);
        ASSERT_EQUAL(deque[2],1);

        deque.PushBack(4);
        ASSERT_EQUAL(deque.Size(),4);
        ASSERT_EQUAL(deque[0],3);
        ASSERT_EQUAL(deque[1],2);
        ASSERT_EQUAL(deque[2],1);
        ASSERT_EQUAL(deque[3],4);
    }

    {
        Deque<int> deque;
        deque.PushBack(1);
        ASSERT_EQUAL(deque[0],1);
        ASSERT_EQUAL(deque.Back(),deque.Front());
        deque.PushBack(2);
        deque.PushBack(3);
        ASSERT_EQUAL(deque[0], 1);
        ASSERT_EQUAL(deque[1], 2);
        ASSERT_EQUAL(deque[2], 3);
        deque.PushFront(4);
        ASSERT_EQUAL(deque[0], 4);
        ASSERT_EQUAL(deque[1], 1);
        ASSERT_EQUAL(deque[2], 2);
        ASSERT_EQUAL(deque[3], 3);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, DequeTests);
    deque<int> true_deq;
    true_deq.push_back(1);
    true_deq.push_front(2);

    cout << true_deq[0];
    // cout << deq[1];
    // vector<int> a;
    // cout << a.back();
}