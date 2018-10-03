#include <vector>
#include <tuple>
#include "topspin.h"

using namespace std;

#ifndef NODE_H
#define NODE_H
class Node {

    public:
        Node();
        Node(TopSpin& p, int d, Node* ancestor, tuple<char,char> parent_action);
        int getDepth();
        int getHeuristic();
        int getNumChildren();
        bool isSolution();
        Node* getParent();
        void createChildren(); // Generate children
        Node* getChild(int n);
        tuple<char,char> getParentMove();
        void setParent(Node* parent);
        void printNodeInfo();

    private:
        bool exhausted; // you've exhausted all children of the node
        bool leaf;      // i.e. is this a solution?
        TopSpin* puzzle;
        int depth;
        int heuristic;
        Node* parent;
        vector<Node> children;
        tuple<char,char> parent_move; //<op, dir> 
};
#endif
