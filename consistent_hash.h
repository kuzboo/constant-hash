#ifndef CONSISTENT_HASH_H
#define CONSISTENT_HASH_H

#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef unsigned int hash_type;

class Virtual_Node
{
public:
    Virtual_Node() : m_ip(""), m_hash_value(0){}

    Virtual_Node(string ip, hash_type hash_value)
        : m_ip(ip), m_hash_value(hash_value){}

    ~Virtual_Node() { m_data.clear(); }

    string m_ip;//虚拟结点ip地址
    hash_type m_hash_value;//虚拟节点哈希值
    map<hash_type, string> m_data; //与该虚拟节点关联的资源的[哈希值-资源name]
};


class Real_Node
{
public:
    Real_Node() : m_ip(""), cur_max_port(0), m_virtual_node_num(0){}

    Real_Node(string ip) : m_ip(ip), cur_max_port(0), m_virtual_node_num(0){}

    ~Real_Node() { virtual_node_hash_list.clear(); }

    hash_type get_max_port() { return cur_max_port; }

private:
    string m_ip;
    hash_type m_virtual_node_num; //虚拟节点数目
    hash_type cur_max_port;       //端口号 对应虚拟结点
    vector<hash_type> virtual_node_hash_list;
};

class Consistent_Hash
{
public:
    Consistent_Hash() : m_real_node_sum(0), m_virtual_node_sum(0){}
    ~Consistent_Hash()
    {
        m_real_node_map.clear();
        m_virtual_node_map.clear();
        m_hash_vec.clear();
    }

    //根据当前哈希值找到最近结点,返回值为节点在列表中的位置
    hash_type find_nearest_node(hash_type hash_value);

    //将资源定位到虚拟结点上
    hash_type put(string data_id);

    //添加真实结点
    void add_real_node(string &ip, hash_type virtual_node_num);

    //删除真实结点
    void drop_real_node(string ip);

private:
    hash_type m_real_node_sum;    //所有实际结点数目
    hash_type m_virtual_node_sum; //所有虚拟结点数目
    map<string, Real_Node> m_real_node_map;
    map<hash_type, Virtual_Node> m_virtual_node_map; //虚拟节点哈希值-虚拟结点信息
    vector<hash_type> m_hash_vec; //存放所有结点哈希值，从小到大排序
};
#endif