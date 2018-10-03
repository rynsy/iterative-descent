#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include "node.h"
#include "topspin.h"

using namespace std;

Node::Node()
{
    exhausted = leaf = false;
    puzzle = new TopSpin;
    depth = 0;
    parent = NULL;
    parent_move = make_tuple('x','x');
}

Node::Node(TopSpin& p, int d, Node* ancestor, tuple<char,char> parent_action)
{
    puzzle = new TopSpin(p);
    depth  = d;
    parent = ancestor;
   
    if(ancestor == NULL) parent_move = make_tuple('x','x');
    else parent_move = parent_action;

    heuristic = puzzle->heuristicValue();

    if(puzzle->solved()) exhausted = leaf = true;
    else exhausted = leaf = false;
}

int Node::getDepth()
{
    return depth;
}

int Node::getHeuristic()
{
    return puzzle->heuristicValue();
}

int Node::getNumChildren()
{
    return children.size();
}

bool Node::isSolution()
{
    return puzzle->solved();
}

Node* Node::getParent()
{
    return parent;
}

static bool NodeComp(Node first, Node second)
{
    if(first.getHeuristic() < second.getHeuristic())
        return true;
    else
        return false;
}

/*
 *  This function should look at the parent
 *  of this node, get the move it made, 
 *  and generate a puzzle that doesn't undo the
 *  parents move. 
 *  Maybe a node will have a list of tuples
 *  of moves that aren't allowed (moves of the parent
 *  and the moves of the previous child generated). 
 *  The root has 3 children, every node thereafter only
 *  has 2 children.
 */
void Node::createChildren()
{
    TopSpin child1(*puzzle), child2(*puzzle), child3(*puzzle);
    tuple<char,char> child1_move, child2_move;

    if(!exhausted)
    {
        if(parent == NULL)
        {
            child1.rotate('l', 1, false);
            child2.rotate('r', 1, false);
            child3.spin(false);

            children.push_back(Node(child1,depth+1,this, make_tuple('r','l')));
            children.push_back(Node(child2,depth+1,this, make_tuple('r','r')));
            children.push_back(Node(child3,depth+1,this, make_tuple('s','x')));
        }
        else
        {
            if(get<0>(parent_move) == 's')
            {
            //If the last move was a spin, rotate in both directions
                child1.rotate('l', 1, false);
                child1_move = make_tuple('r','l');
                child2.rotate('r', 1, false);
                child2_move = make_tuple('r','r');
            }
            else if(get<0>(parent_move) == 'r')
            {
            //check the direction, and make a child that spins and a
            //child that rotates in the opposite direction
                if(get<1>(parent_move) == 'l')
                {
                    child1.spin(false);
                    child1_move = make_tuple('s','x');
                    child2.rotate('l', 1, false);
                    child2_move = make_tuple('r','l');
                }
                else if(get<1>(parent_move) == 'r')
                {
                    child1.spin(false);
                    child1_move = make_tuple('s','x');
                    child2.rotate('r', 1, false);
                    child2_move = make_tuple('r','r');
                }
                else
                {
                    child1_move = child2_move = make_tuple('x','x');
                }
            }
            else
            {
                child1_move = child2_move = make_tuple('x','x');
            }
            children.push_back(Node(child1, depth+1, this, child1_move));
            children.push_back(Node(child2, depth+1, this, child2_move));
        }
        exhausted = true;
        sort(children.begin(), children.end(), NodeComp);
    }

}

/*
 *  I haven't really decided if I want the search to use an
 *  iterator-type thing or if I want it to call getChild with 
 *  increasing values of n
 */
Node* Node::getChild(int n)
{
    if(!exhausted)
      createChildren();
    if(!leaf)
    {
        if(n < children.size() && n >= 0)
        {
            return &(children.at(n));        
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

tuple<char, char> Node::getParentMove()
{
    return parent_move;
}

void Node::setParent(Node* p)
{
    parent = p;
}

void Node::printNodeInfo()
{
    string str(30,'#');

    cout << endl << str << endl;
    cout << "Exhausted: " << exhausted << endl;
    cout << "Leaf: " << leaf << endl;
    cout << "Depth: " << depth << endl;
    cout << "Heuristic: " << heuristic << endl;
    cout << "parent (addr): " << parent << endl;
    cout << "Size of <vect> children: " << children.size() << endl;
    cout << "The move from the parent: " << get<0>(parent_move) << ", " << get<1>(parent_move) << endl;
    cout << "Puzzle->print() output: " << endl;
    puzzle->print();
    cout << endl << str << endl;
}
