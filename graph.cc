#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <class K, class V>
inline bool exist_in_map(const K &k, const unordered_map<K, V> &map) {
  return map.find(k) != map.end();
}

template <class K, class V> class Graph {
    using adjacent_list_ptr= shared_ptr<vector<K>>;
private:
  unordered_map<K, V> nodes;
  unordered_map<K, adjacent_list_ptr> adjacent_lists;

public:
  Graph() {}
  ~Graph() {}
  void add_node(const K &key, const V &value) { nodes[key] = value; }
  void print_graph() ;
  void add_edge(const K &from, const K &to);
  adjacent_list_ptr get_neighbors_by_node(const K &);

};



template <class K, class V>
void Graph<K, V>::print_graph() {
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

template <class K, class V>
void Graph<K, V>::add_edge(const K &from, const K &to) {
  if (!exist_in_map(from, nodes)) {
    throw runtime_error("node does not exist!");
  } else if (!exist_in_map(to, nodes)) {
    throw runtime_error("node does not exist!");
  }
  if (!exist_in_map(from, adjacent_lists)) {
    adjacent_list_ptr vp{new vector<K>{to}};
    auto p = make_pair(from, move(vp));
    adjacent_lists.insert(move(p));
  } else {
    adjacent_lists[from]->push_back(to);
  }
}

int main() {

  Graph<string, int> g;
  g.add_node("a", 1);
  g.add_node("b", 2);
  g.add_node("c", 3);
  g.add_edge("a", "b");
  g.add_edge("b", "c");
  g.print_graph();
  g.add_edge("k", "c");
}
