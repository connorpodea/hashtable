#include <iostream>
#include <string>
#include <cmath>
#include "hash.h"

using namespace std;

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

class HashTable
{
private:
    int k_count;
    Node **ptr_arr;

public:
    HashTable()
    {
        this->k_count = 10;
        ptr_arr = new Node *[k_count];
    }

    HashTable(int k_count)
    {
        this->k_count = k_count;
        ptr_arr = new Node *[k_count];
    }

    void load(Node *new_node)
    {
        int index = hash_function(new_node->data) % k_count;
        Node *head = ptr_arr[index];
        new_node->next = head;
        head = new_node;
    }

    int get_k_count()
    {
        return this->k_count;
    }

    double get_mean()
    {
        double sum = 0;

        for (int i = 0; i < this->get_k_count(); i++)
        {
            sum += get_list_size(i);
        }
        return sum / this->get_k_count();
    }

    double get_std_dev()
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
    }

    int get_list_size(int index)
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

    void print_first_five_lists()
    {
        for (int i = 0; i < 5; i++)
        {
            print_list(i);
            cout << "\n";
        }
    }

    void print_list(int index)
    {
        Node *trav = ptr_arr[index];

        cout << "Contents of index " << index << ": ";
        while (trav->next != nullptr)
        {
            cout << trav->data << ", ";
            trav = trav->next;
        }
        cout << trav->data;
    }

    void print_list_lengths()
    {
        for (int i = 0; i < this->get_k_count(); i++)
        {
            cout << "Index " << i << " has " << get_list_size(i) << " elements.";
            cout << "\n";
        }
    }
};

int hash_function(string text)
{
    int sum = 0;

    for (int i = 0; i < text.length(); i++)
    {
        sum += text.at(i);
    }

    return sum;
}
