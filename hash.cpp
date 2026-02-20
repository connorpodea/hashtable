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

// reference for this hash function: https://nvlpubs.nist.gov/nistpubs/Legacy/FIPS/fipspub180-1.pdf

// 512 bit string creation:
// left shift the string by 1, and add 1
// left shift (512-lengthOfString) times, and add (lengthOfString)

// functions used:
// f_t(B,C,D) = (B & C) | (~B & D)                 for (0 <= t <= 19)
// f_t(B,C,D) = (B XOR C XOR D)                    for (20 <= t <= 39)
// f_t(B,C,D) = (B & C) | (B & D) | (C & D)        for (40 <= t <= 59)
// f_t(B,C,D) = (B ^ C ^ D)                        for (60 <= t <= 79)

// constants used:
// K_t = (5A827999)_16                             for (0 <= t <= 19)
// K_t = (6ED9EBA1)_16                             for (20 <= t <= 39)
// K_t = (8F1BBCDC)_16                             for (40 <= t <= 59)
// K_t = (CA62C1D6)_16                             for (60 <= t <= 79)

// initial values of 5 word buffers
// H_0 = (67452301)_16
// H_1 = (EFCDAB89)_16
// H_2 = (98BADCFE)_16
// H_3 = (10325476)_16
// H_4 = (C3D2E1F0)_16

// word block (512 bit block using modified intial value)
// divide into 16 words: W_0, W_1, W_2, ..., W_15

// The circular left shift operation S^(n)(X), where X is a word and n is an integer
// with 0 <= n < 32, is defined by
// S^(n)(X) = (X << n) | (X >> 32-n)

// algorithm
// for (t >= 16), let W_t = S^1(W_(t-3) XOR W(t-8) XOR W(t-14) XOR W(t-16))
// let A = H_0, B = H_1, C = H_2, D = H_3, E = H_4
// for (t >= 0) {
//      TEMP = S^5(A) + f_t(B,C,D) + E + W_t + K_t}
//      E = D; D = C, C = S^(30)(B); B = A; A = TEMP;
// }
// Let H_0 = H_0 + A, H_1 = H_1 + B, H_2 = H_2 + C, H_3 = H_3 + D, H_4 = H_4 + E
//
// after processing M_n, the hash is the 160 bit string represented by the 5 words
// H_0 H_1 H_2 H_3 H_4

int HashTable::hash_function(string key)
{
    uint32 *word_blocks = new uint32[16];
    int beginning_word_index = 0;

    // initial constants
    uint32 K_t = 0x0;

    uint32 H_0 = 0x67452301;
    uint32 H_1 = 0xEFCDAB89;
    uint32 H_2 = 0x98BADCFE;
    uint32 H_3 = 0x10325476;
    uint32 H_4 = 0xC3D2E1F0;

    uint32 A = H_0;
    uint32 B = H_1;
    uint32 C = H_2;
    uint32 D = H_3;
    uint32 E = H_4;

    uint32 TEMP;
    uint32 W_t;

    for (int t = 0; t < 80; t++)
    {
        if (t >= 16)
        {
            W_t = get_S(1, word_blocks[(t - 3) % 16] ^ word_blocks[(t - 8) % 16] ^ word_blocks[(t - 14) % 16] ^ word_blocks[(t - 16) % 16]);
        }
        else
        {
            W_t = word_blocks[t];
        }

        TEMP = get_S(5, A) + get_f(B, C, D, t) + E + W_t + get_K(t);
        E = D;
        D = C;
        C = get_S(30, B);
        B = A;
        A = TEMP;
    }
    H_0 = H_0 + A;
    H_1 = H_1 + B;
    H_2 = H_2 + C;
    H_3 = H_3 + D;
    H_4 = H_4 + E;

    // unsure how to return the final hash since i would need to compute (160bit_int % k_count)
    // temp return val:
    return 0;
}

uint32 get_S(uint32 n, uint32 X)
{
    return (X << n) | (X >> 32 - n);
}

uint32 get_K(int t)
{
    if (t <= 19)
    {
        return 0x5A827999;
    }
    else if (t <= 39)
    {
        return 0x6ED9EBA1;
    }
    else if (t <= 59)
    {
        return 0x8F1BBCDC;
    }
    else if (t <= 79)
    {
        return 0xCA62C1D6;
    }
    else
    {
        // should never be reached
        return 0x0;
    }
}

uint32 get_f(uint32 B, uint32 C, uint32 D, int t)
{
    if (t <= 19)
    {
        return ((B & C) | (~B & D));
    }
    else if (t <= 39)
    {
        return (B ^ C ^ D);
    }
    else if (t <= 59)
    {
        return ((B & C) | (B & D) | (C & D));
    }
    else if (t <= 79)
    {
        return (B ^ C ^ D);
    }
    else
    {
        // should never be reached
        return 0x0;
    }
}