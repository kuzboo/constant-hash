#include<iostream>
#include"consistent_hash.h"
using namespace std;

int main()
{
    Consistent_Hash hash = Consistent_Hash();
    cout << "-------------------------add real node-------------------------" << endl;
    hash.add_real_node("192.168.199.2", 300);
    hash.add_real_node("192.168.199.101", 300);
    hash.add_real_node("192.168.133.145", 300);
    cout << "-------------------------insert data---------------------------" << endl;
    hash.insert("c++");
    hash.insert("Go");
    hash.insert("Python");
    hash.insert("C");
    hash.insert("Java");
    hash.insert("China");
    hash.insert("Tai wan sheng");
    hash.insert("xiao ri ben");
    cout << "-------------------------print node-------------------------   " << endl;
    hash.print();
}