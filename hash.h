// hash.h
#include <iostream>
#include <string>
#include <cmath>
// You are free to use additional libraries as long as it's not PROHIBITED per instruction.

using namespace std;

struct Node
{
    string data;
    Node *next;
    Node(string input) : data(input), next(nullptr) {}
};

class HashTable
{
private:
    int k_count;
    Node **ptr_arr;

public:
    HashTable(int k);
    void load(string data);
    double get_std_dev();
    int get_list_size(int index);
    void print_first_five_lists();
    void print_slot_lengths();
    void print_std_dev();
};

int hash_function(string text);