#include <boost/any.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <class K, class... Args>
inline bool exist_in_map(const K &k, const unordered_map<K, Args...> &map) {
    return map.find(k) != map.end();
}

typedef unordered_map<string, boost::any> attr;

template <class A, class B>
struct PairHash {
    std::size_t operator()(pair<A, B> p) const {
        return std::hash<A>{}(p.first) ^ (std::hash<B>{}(p.second) << 1);
    }
};

template <class K>
class Graph {
    using adjacent_list_ptr = shared_ptr<vector<K>>;

   private:
    unordered_map<K, unique_ptr<attr>> nodes;
    unordered_map<K, adjacent_list_ptr> adjacent_lists;
    unordered_map<pair<K, K>, unique_ptr<attr>, PairHash<K, K>> edge_attrs;

   public:
    Graph() {}
    ~Graph() {}
    void init_adjlist(const K &key) {
        if (!exist_in_map(key, adjacent_lists)) {
            adjacent_list_ptr vp{new vector<K>{}};
            adjacent_lists[key] = vp;
        }
    }
    void add_node(const K &key) {
        nodes[key] = unique_ptr<attr>{new attr{}};
        init_adjlist(key);
    }
    void add_node(const K &key, const attr &a);
    void set_node_attr(const K &key, const attr &a);
    void add_node_attr(const K &key, const string &attr_name, boost::any &value);
    boost::any get_node_attr(const K &key, const string &attr_name);
    void print_graph();
    void add_edge(const K &from, const K &to);
    void add_edge_attr(const K &from, const K &to, const string &key,
                       boost::any &value);
    boost::any get_edge_attr(const K &from, const K&to, const string &key);
    void set_edge_weight(const K&from, const K &to, int weight);
    int get_edge_weight(const K&from, const K &to);
    adjacent_list_ptr get_neighbors_by_node(const K &);
};

template<class K>
void Graph<K>::set_edge_weight(const K&from, const K &to, int weight){
    auto w = boost::any{weight};
    add_edge_attr(from, to, "weight", w);
}

template<class K>
int Graph<K>::get_edge_weight(const K&from, const K &to){
    return boost::any_cast<int>(get_edge_attr(from, to, "weight"));
}

template <class K>
boost::any Graph<K>::get_edge_attr(const K&from, const K&to, const string &key){
   return (*edge_attrs[make_pair(from, to)])[key];
}

template <class K>
void Graph<K>::add_node_attr(const K &key, const string &attr_name,
                             boost::any &value) {
    nodes[key][attr_name] = value;
}

template <class K>
boost::any Graph<K>::get_node_attr(const K &key, const string &attr_name) {
    return nodes[key][attr_name];
}

template <class K>
void Graph<K>::add_node(const K &key, const attr &a) {
    unique_ptr<attr> tmp{new attr{}};
    *tmp = a;
    nodes[key] = std::move(tmp);
    init_adjlist(key);
}

template <class K>
void Graph<K>::set_node_attr(const K &key, const attr &a) {
    nodes[key] = a;
}

template <class K>
void Graph<K>::print_graph() {
    for (auto &x : nodes) {
        cout << x.first << endl;
    }
    for (auto &x : adjacent_lists) {
        cout << x.first << " : ";
        for (auto &e : *x.second) {
            cout << e << " ";
        }
        cout << endl;
    }
}

template <class K>
void Graph<K>::add_edge(const K &from, const K &to) {
    if (!exist_in_map(from, nodes)) {
        throw runtime_error("node does not exist!");
    } else if (!exist_in_map(to, nodes)) {
        throw runtime_error("node does not exist!");
    }
    pair<K, K> np{from, to};
    if (exist_in_map(np, edge_attrs)) {
        throw runtime_error("the edge already exist");
    }
    adjacent_lists[from]->push_back(to);
    edge_attrs[np] = unique_ptr<attr>{new attr{}};
}
template <class K>
void Graph<K>::add_edge_attr(const K &from, const K &to, const string &attr_name,
                             boost::any &value) {
    pair<K, K> np{from, to};
    (*edge_attrs[np])[attr_name] = value;
}
