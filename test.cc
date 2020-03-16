#include <cassert>
#include <string>

#include "graph.cc"
// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

void test_add_node() {
    Graph<string> g;
    g.add_node("a");
    g.add_node("b");
    g.add_node("c");
    g.add_edge("a", "b");
    g.add_edge("b", "c");
    g.add_edge("k", "c");
    g.add_edge("a", "c");
    g.add_edge("a", "m");
    g.print_graph();
}
int test_add_edge() {
    Graph<string> g;
    g.add_node("a");
    g.add_node("c");
    g.add_edge("a", "c");
    try {
        g.add_edge("a", "c");

    } catch (std::runtime_error &e) {
        return 0;
    }
    assertm(false, "add existing edge should raise");
}

int test_add_weight() {
    Graph<string> g;
    g.add_node("a");
    g.add_node("c");
    g.add_edge("a", "c");
    g.set_edge_weight("a", "c", 1456);
    assertm(g.get_edge_weight("a", "c") == 1456, "test set weight error");
    return 0;
}

int main() {
    test_add_node();
    test_add_edge();
    test_add_weight();
}
