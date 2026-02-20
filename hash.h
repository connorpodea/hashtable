#include <iostream>
#include <string>
#include <cmath>
// You are free to use additional libraries as long as it's not PROHIBITED per instruction.

using namespace std;

struct Node
{
    string key;
    Node *next;
    Node();
    Node(string key);
};

class HashTable
{
private:
    int k_count;
    Node **ptr_arr;
    int *slot_sizes;

public:
    HashTable();
    HashTable(int k);
    int get_k_count();
    void load(string key);
    double get_std_dev();
    void print_list(int index);
    void print_first_five_lists();
    void print_slot_lengths();
    void print_std_dev();
    int hash_function(string key);
};

typedef unsigned int uint32;
uint32 get_S(uint32 n, uint32 X);
uint32 get_K(int t);
uint32 get_f(uint32 B, uint32 C, uint32 D, int t);