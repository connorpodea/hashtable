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

public:
    HashTable();
    HashTable(int k);
    int get_k_count();
    void load(string key);
    double get_mean();
    double get_std_dev();
    int get_list_size(int index);
    void print_list(int index);
    void print_first_five_lists();
    void print_slot_lengths();
    void print_std_dev();
};

int hash_function(string key);