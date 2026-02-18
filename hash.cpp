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
    ptr_arr = new Node *[k_count];

    for (int i = 0; i < this->get_k_count(); i++)
    {
        ptr_arr[i] = nullptr;
    }
}

HashTable::HashTable(int k_count)
{
    this->k_count = k_count;
    ptr_arr = new Node *[k_count];

    for (int i = 0; i < k_count; i++)
    {
        ptr_arr[i] = nullptr;
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
}

double HashTable::get_mean()
{
    double sum = 0;
    for (int i = 0; i < this->get_k_count(); i++)
    {
        sum += get_list_size(i);
    }
    return sum / this->get_k_count();
}

double HashTable::get_std_dev()
{
    double std_dev = 0;
    double sum = 0;
    double mean = get_mean();

    for (int i = 0; i < this->get_k_count(); i++)
    {
        int x_i = get_list_size(i);
        sum += (x_i - mean) * (x_i - mean);
    }
    sum /= this->get_k_count();
    std_dev = sqrt(sum);
    return std_dev;
}

int HashTable::get_list_size(int index)
{
    Node *trav = ptr_arr[index];
    int size = 0;
    while (trav != nullptr)
    {
        size++;
        trav = trav->next;
    }
    return size;
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
    for (int i = 0; i < this->get_k_count(); i++)
    {
        cout << "Slot " << i << ": ";
        cout << get_list_size(i) << "\n";
    }
}

void HashTable::print_std_dev()
{
    cout << "==== Printing the standard deviation ====\n";
    cout << get_std_dev() << endl;
}

int hash_function(string key)
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum += key.at(i) * i;
    }
    return sum;
}