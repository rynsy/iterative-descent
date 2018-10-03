#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include "global.h"
#include "node.h"
#include "ida.h"

using namespace std;

Node* SOLUTION = NULL;

void printPath()
{
    stack<tuple<char,char>> moves;
    tuple<char,char> current_move;
    string spacer(30, '#');
    Node* tail = SOLUTION;

    while(tail != NULL)
    {
        moves.push(tail->getParentMove());
        tail = tail->getParent();
    }

    cout << endl << spacer 
         << endl << "Number of moves: " << moves.size() - 1
         << endl << spacer;

    while(!moves.empty())
    {
        current_move = moves.top();
        cout << endl << "Operation: " << get<0>(current_move)
             << endl << "Direction: " << get<1>(current_move)
             << endl << spacer << endl;
        moves.pop();
    }

}

void IDA(Node* start, int starting_bound)
{
    int t, it, bound;
    string str(30, '#');

    t = it = 0;
    bound = starting_bound;

    while(it < bound)
    {
        t = search(start, 0, bound);
        if( t == FOUND )
        {
            cout << endl << str << endl << "FOUND IT!"; 
            cout << endl << str << endl;
            break;
        }
        if( t == INF ) 
        {
            cout << endl << str << endl << "Couldn't find it.. :<"
                 << endl << str << endl;
            break;
        }
        bound = t;
        it++;
    }
}

int search(Node* node, int g, int bound)
{
   int f, t, min, num_children;
   Node* child;
   
   f = g + node->getHeuristic();
   
   if( f > bound ) return f;
   if( node->isSolution() )
   {
       SOLUTION = node;
       return FOUND;
   }
   min = INF;
   node->createChildren(); 
   num_children = node->getNumChildren();

   for(int i = 0; i < num_children; i++)
   {
        child = node->getChild(i);
        if(child != NULL)
            t = search(child, g+1, bound);
        if( t == FOUND  )
        {
            return FOUND;
        }
        if( t < min ) min = t;    
   } 
   return min;
}
