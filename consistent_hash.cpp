#include"consistent_hash.h"
#include<iostream>
using namespace std;

const int HASH_LEN = 32;

/*获取哈希值*/
unsigned int my_getMurMurHash(const void *key, int len) 
{
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    const int seed = 97;
    unsigned int h = seed ^len;
    // Mix 4 bytes at a time into the hash
    const unsigned char *data = (const unsigned char *) key;
    while (len >= 4) {
        unsigned int k = *(unsigned int *) data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }
    // Handle the last few bytes of the input array
    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}



hash_type Consistent_Hash::find_nearest_node(hash_type hash_value)
{
    int low = 0;
    int high = m_hash_vec.size();
    int mid;

    if (hash_value > m_hash_vec[high-1])
    {
        return 0;
    }
    
    while(low<high)
    {
        mid = low + (high - low) / 2;
        if (m_hash_vec[mid] == hash_value)
        {
            return mid;
        }
        else if(m_hash_vec[mid]>hash_value)
        {
            high = mid;
        }
        else
            low = mid + 1;
    }
    return low;
}

void Consistent_Hash::add_real_node(string& ip,hash_type virtual_node_num)
{
    cout << "[add real node:]" << ip << endl;

    //定义一个真实结点
    Real_Node *real_node;

    //如果该ip结点已经有映射,直接取出
    if (m_real_node_map.find(ip) != m_real_node_map.end())
    {
        real_node = &m_real_node_map[ip];
    }
    //如果没有则新建结点
    else
    {
        real_node = new Real_Node(ip);
        m_real_node_sum++;
    }

    hash_type cur_port = real_node->cur_max_port;
    hash_type cur_vir_node_num = 0;
    hash_type vir_hash;
    string vir_ip;

    while (cur_vir_node_num < virtual_node_num)
    {
        /*添加一个虚拟节点*/
        do{
            cur_port++;
            vir_ip = ip + ":" + to_string(cur_port);               //虚拟节点ip值;
            vir_hash = my_getMurMurHash(vir_ip.c_str(), HASH_LEN); //虚拟节点哈希值;
        } 
        //如果虚拟节点集合中已经有了该结点，则port继续增加，计算新的哈希值
        //找到一个集合中没有的新虚拟节点
        while (m_virtual_node_map.find(vir_hash)!=m_virtual_node_map.end()); 

        cur_vir_node_num++;
        // m_virtual_node_map[vir_hash] = Virtual_Node(vir_ip, vir_hash); //添加到虚拟节点集合中;
        // m_hash_vec.push_back(vir_hash);                                //添加到总的集合中;
        //【这样子会内存爆炸】
        Virtual_Node *vir_node = new Virtual_Node(vir_ip, vir_hash); //new一个新的虚拟节点
        m_virtual_node_map[vir_hash] = *vir_node;                    //添加到总的虚拟节点集合中
        m_hash_vec.push_back(vir_hash);                              //添加到数组中
        sort(m_hash_vec.begin(), m_hash_vec.end());                  //从小到大排序

        /* 建立一个新的虚拟节点 需要进行数据迁移 */
        hash_type id = find_nearest_node(vir_hash);//找到虚拟节点的最近结点
        hash_type next_id = id + 1;                //下一个结点
        if (next_id >= m_hash_vec.size())
            next_id = 0;
        hash_type next_hash = m_hash_vec[next_id];

        //记录next_id上要删除的资源的哈希值
        vector<hash_type> tobe_delete;
        //与next_hash这个虚拟节点关联的资源
        map<hash_type, string> *tobe_robbed = &m_virtual_node_map[next_hash].m_data;
        //遍历这些资源
        for (auto data = tobe_robbed->begin(); data != tobe_robbed->end(); ++data)
        {
            /*如果这个next_id对应的资源的哈希值在新创建的这个虚拟节点的前面*/
            /*就要重新关联了*/
            if(data->first<vir_hash)
            {
                m_virtual_node_map[vir_hash].m_data[data->first] = data->second;
                tobe_delete.push_back(data->first);
            }
        }

        //删除next_id上的资源
        for(auto deleted:tobe_delete)
        {
            tobe_robbed->erase(deleted);
            cout << "[move data] " << deleted << " from node:" << m_virtual_node_map[next_hash].m_ip
                 << "(" << next_hash << ") to" << m_virtual_node_map[vir_hash].m_ip
                 << "(" << vir_hash << ")" << endl;
        }
    }
    real_node->cur_max_port = cur_port;
    real_node->m_virtual_node_num += cur_vir_node_num;//当前真实结点的虚拟节点数目
    m_real_node_map[ip] = *real_node;//添加到真实结点集合中

    m_virtual_node_sum += cur_vir_node_num;//总的虚拟节点数目

    cout << "[add real node finished]" << ip << endl;
}

/*定位资源，请求的资源*/
hash_type Consistent_Hash::put(string data_name)
{
    //对资源进行第一次哈希映射
    hash_type data_hash = my_getMurMurHash(data_name.c_str(), HASH_LEN);

    //顺时针找到最近的结点index，和对应的哈希值
    hash_type nearest_index = find_nearest_node(data_hash);
    hash_type nearest_hash = m_hash_vec[nearest_index];

    //关联虚拟结点和资源
    m_virtual_node_map[nearest_hash].m_data.insert(make_pair(data_hash, data_name));

    cout << "data: " << data_name << "(" << data_hash << ")\twas put on virtual node:"
         << m_virtual_node_map[nearest_hash].m_ip << "(" << nearest_hash << ")"
         << endl;

    return nearest_hash;
}