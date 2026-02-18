#include <iostream>
#include <string>
#include <cmath>
#include "hash.h"

using namespace std;

Node::Node()
{
    key = "";
    next = nullptr;
}

Node::Node(string key)
{
    this->key = key;
    this->next = nullptr;
}

HashTable::HashTable()
{
    this->k_count = 10;
    this->ptr_arr = new Node *[k_count];
    this->slot_sizes = new int[k_count];

    for (int i = 0; i < this->get_k_count(); i++)
    {
        ptr_arr[i] = nullptr;
        slot_sizes[i] = 0;
    }
}

HashTable::HashTable(int k_count)
{
    this->k_count = k_count;
    this->ptr_arr = new Node *[k_count];
    this->slot_sizes = new int[k_count];

    for (int i = 0; i < k_count; i++)
    {
        ptr_arr[i] = nullptr;
        slot_sizes[i] = 0;
    }
}

int HashTable::get_k_count()
{
    return this->k_count;
}

void HashTable::load(string key)
{
    int index = hash_function(key) % k_count;

    Node *new_node = new Node(key);
    new_node->next = ptr_arr[index];
    ptr_arr[index] = new_node;
    slot_sizes[index] += 1;
}

double HashTable::get_std_dev()
{
    double mean = 0;
    double variance = 0;

    int k_count = this->get_k_count();

    for (int i = 0; i < k_count; i++)
    {
        mean += this->slot_sizes[i];
    }
    mean /= k_count;

    for (int i = 0; i < k_count; i++)
    {
        int x_i = this->slot_sizes[i];
        variance += (x_i - mean) * (x_i - mean);
    }
    variance /= k_count;

    return sqrt(variance);
}

void HashTable::print_list(int index)
{
    Node *trav = ptr_arr[index];
    while (trav != nullptr)
    {
        cout << trav->key << " ";
        trav = trav->next;
    }
}

void HashTable::print_first_five_lists()
{
    cout << "==== Printing the contents of the first 5 slots ====\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "Slot " << i << ": ";
        print_list(i);
        cout << "\n";
    }
}

void HashTable::print_slot_lengths()
{
    cout << "==== Printing the slot lengths ====\n";
    int k_count = this->get_k_count();
    for (int i = 0; i < k_count; i++)
    {
        cout << "Slot " << i << ": ";
        cout << this->slot_sizes[i] << "\n";
    }
}

void HashTable::print_std_dev()
{
    cout << "==== Printing the standard deviation ====\n";
    cout << get_std_dev() << endl;
}

int hash_function(string key)
{
    int hash_val = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash_val += key.at(i) * i;
    }
    return hash_val;
}