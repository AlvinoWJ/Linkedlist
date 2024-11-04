#include <iostream>
using namespace std;

typedef struct
{
    string ID, nama;
    float harga;
} itemjual;

int main()
{
    itemjual item[100];
    item[0].nama = "coklat";

    return 0;
}