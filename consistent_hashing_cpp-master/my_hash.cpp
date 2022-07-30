#include "my_hash.h"

int HASH_LEN = 32;

unsigned int my_getMurMurHash(const void *key, int len) {
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

virtual_node::virtual_node(string ip, unsigned int hash_value) {
    ip = ip;
    hash_value = hash_value;
}

virtual_node::~virtual_node() {
    data.clear();
}

virtual_node::virtual_node() {
    ip = "";
    hash_value = 0;
}


real_node::real_node(string ip) {
    ip = ip;
    cur_max_port = 0;
    virtual_node_num = 0;
}

real_node::~real_node() {
    virtual_node_hash_list.clear();
}

real_node::real_node() {
    ip = "";
    cur_max_port = 0;
    virtual_node_num = 0;
}

consistent_hash::consistent_hash() {
    real_node_sum = 0;
    virtual_node_sum = 0;
}

consistent_hash::~consistent_hash() {
    virtual_node_map.clear();
    real_node_map.clear();
    sorted_node_hash_list.clear();
}

unsigned int consistent_hash::find_nearest_node(unsigned int hash_value) {
    int low = 0;
    int high = sorted_node_hash_list.size() - 1;
    int mid;
    if (hash_value > sorted_node_hash_list[high]) {
        return 0;
    }
    while (low < high) {
        mid = (low + high) / 2;
        if (sorted_node_hash_list[mid] == hash_value) {
            return mid;
        } else if (sorted_node_hash_list[mid] > hash_value) {
            high = mid;
        } else {//sorted_node_hash_list[mid]<data_hash
            low = mid + 1;
        }
    }
    return low;
}

void consistent_hash::add_real_node(string ip, unsigned int virtual_node_num) {
    cout << "[add_real_node]\t" << ip << endl;
    real_node *node;
    if (real_node_map.find(ip) != real_node_map.end()) {
        node = &real_node_map[ip];
    } else {
        real_node new_node = real_node(ip);
        node = &new_node;
        real_node_sum++;
    }
    int cur_port = node->cur_max_port;
    int vir_node_num = 0;
    string tmp_ip;
    unsigned int tmp_hash;
    while (vir_node_num < virtual_node_num) {
        do {
            cur_port++;
            tmp_ip = ip + ":" + to_string(cur_port);
            tmp_hash = my_getMurMurHash(tmp_ip.c_str(), HASH_LEN);
        } while (virtual_node_map.find(tmp_hash) != virtual_node_map.end());
        vir_node_num++;
        
        virtual_node *vir_node=new virtual_node(tmp_ip, tmp_hash);
        virtual_node_map[tmp_hash] = *vir_node;
        delete vir_node;

        sorted_node_hash_list.push_back(tmp_hash);
        sort(sorted_node_hash_list.begin(), sorted_node_hash_list.end());
        unsigned int id = find_nearest_node(tmp_hash);
        unsigned int next_id = id + 1;
        if (next_id >= sorted_node_hash_list.size()) {
            next_id = 0;
        }
        unsigned int next_hash = sorted_node_hash_list[next_id];
        vector<unsigned int> tobe_deleted;

        //next_hash虚拟结点对应的资源
        map<unsigned int, string> *tobe_robbed = &(virtual_node_map[next_hash].data);
        //遍历这个虚拟机结点关联的资源
        for (auto data = tobe_robbed->begin(); data != tobe_robbed->end(); data++) {
            if (data->first < tmp_hash) {
                virtual_node_map[tmp_hash].data[data->first] = data->second;
                tobe_deleted.push_back(data->first);
            }
        }
        for (auto deleted:tobe_deleted) {
            tobe_robbed->erase(deleted);
            cout << "[move data]\t" << deleted << "\tfrom node:\t" << virtual_node_map[next_hash].ip << "("
                 << next_hash << ")" << "\tto\t"
                 << virtual_node_map[tmp_hash].ip << "(" << tmp_hash << ")" << endl;
        }
        node->virtual_node_hash_list.push_back(tmp_hash);
    }
    node->cur_max_port = cur_port;
    node->virtual_node_num += virtual_node_num;
    real_node_map[ip] = *node;

    virtual_node_sum += virtual_node_num;
    cout << "[add_real_node finished]\t" << ip << endl << endl;
}


void consistent_hash::print_real_node(string ip) {
    cout << "------------consistent_hash.print_real_node------------" << endl;
    cout << "real_node ip:" << ip << "\tvirtual_node_num=" << real_node_map[ip].virtual_node_num << endl;
    for (auto tmp:real_node_map[ip].virtual_node_hash_list) {
        if (virtual_node_map[tmp].data.size() > 0) {
            cout << "virtual node:\t" << virtual_node_map[tmp].ip << "(" << tmp << ")" << "\thas data:";
            for (auto data:virtual_node_map[tmp].data) {
                cout << "(" << data.second << "," << data.first << ")\t";
            }
            cout << endl;
        }
    }
    cout << endl;
}

void consistent_hash::print() {
    cout << endl << "------------consistent_hash.print()------------" << endl;
    cout << "real_node_sum:\t" << real_node_sum << "\tvirtual_node_sum:\t" << virtual_node_sum << endl;
    cout << endl;
    for (auto tmp = real_node_map.begin(); tmp != real_node_map.end(); tmp++) {
        print_real_node(tmp->first);
    }

}


unsigned int consistent_hash::put(string data_id) {
    unsigned int data_hash = my_getMurMurHash(data_id.c_str(), HASH_LEN);
    unsigned int id = find_nearest_node(data_hash);
    unsigned int put_on_virnode_hash = sorted_node_hash_list[id];
    virtual_node_map[put_on_virnode_hash].data.insert(make_pair(data_hash, data_id));
    cout << "data:\t" << data_id << "(" << data_hash << ")\twas put on virtual node:"
         << virtual_node_map[put_on_virnode_hash].ip << "(" << put_on_virnode_hash << ")"
         << endl;
    return 0;
}

void consistent_hash::drop_real_node(string ip) {
    cout << "[drop_real_node]\t" << ip << endl;
    vector<unsigned int> *virtual_hash_list_p = &real_node_map[ip].virtual_node_hash_list;
    sort(virtual_hash_list_p->begin(), virtual_hash_list_p->end());
    unsigned int next_id;
    unsigned int next_hash;
    unsigned int cur_id;
    unsigned int cur_hash;
    vector<unsigned int> tobe_delete;
    for (int i = virtual_hash_list_p->size() - 1; i >= 0; i--) {
        cur_hash = (*virtual_hash_list_p)[i];
        tobe_delete.push_back(cur_hash);
        if (virtual_node_map[cur_hash].data.size() > 0) {
            cur_id = find_nearest_node(cur_hash);
            next_id = cur_id;
            string next_realnode_ip;
            do {
                next_id++;
                if (next_id >= sorted_node_hash_list.size()) {
                    next_id = 0;
                }
                next_hash = sorted_node_hash_list[next_id];
                next_realnode_ip = virtual_node_map[next_hash].ip;
            } while (next_realnode_ip.find(ip) != -1);
            map<unsigned int, string> *moveto = &(virtual_node_map[next_hash].data);
            for (auto &data : virtual_node_map[cur_hash].data) {
                (*moveto)[data.first] = data.second;
                cout << "[move data]\t" << data.second << "\tfrom node:\t" << virtual_node_map[cur_hash].ip << "("
                     << cur_hash << ")" << "\tto\t"
                     << virtual_node_map[next_hash].ip << "(" << next_hash << ")" << endl;
            }
        }
    }
    for (auto hash:tobe_delete) {
        virtual_node_map.erase(cur_hash);
        virtual_node_sum--;
        auto iter = find(sorted_node_hash_list.begin(),
                         sorted_node_hash_list.end(), hash);
        if (iter != sorted_node_hash_list.end()) {
            sorted_node_hash_list.erase(iter);
        }
    }
    sort(sorted_node_hash_list.begin(), sorted_node_hash_list.end());
    real_node_map[ip].virtual_node_hash_list.clear();
    real_node_map.erase(ip);
    real_node_sum--;
    cout << "[drop_real_node finished]\t" << ip << endl << endl;
}

