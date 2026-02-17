#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

int hash_function(string text)
{
    // Implement your own hash function here
    int sum = 0;
    for (int i = 0; i < text.length(); i++)
    {
        sum += text.at(i);
    }
    return sum;
}

struct Node
{
    string data;
    Node *next;

    Node()
    {
        data = "";
        next = nullptr;
    }

    Node(string input)
    {
        this->data = input;
        this->next = nullptr;
    }
};