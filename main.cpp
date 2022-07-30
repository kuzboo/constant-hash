#include<iostream>
#include"consistent_hash.h"
using namespace std;

int main()
{
    Consistent_Hash hash = Consistent_Hash();
    hash.add_real_node("192.168.199.2", 300);

    hash.insert("c++");
}