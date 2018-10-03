#include <iostream>
#include <string>
#include "global.h"
#include "topspin.h"
#include "randomizer.h"
#include "node.h"
#include "ida.h"

using namespace std;

void menu()
{
    int n;
    string spacer(30,'#');
    char choice;
    TopSpin* puzzle = new TopSpin();
    bool pprint = false;

    while( choice != 'q' )
    {
        cout << spacer << endl;
        cout << "CURRENT PUZZLE" << endl;
        puzzle->print();
        cout << spacer << endl;
        cout << "1. Move wheel left or right" << endl
             << "2. Spin the wheel" << endl
             << "3. Clear puzzle" << endl
             << "4. Generate random puzzle" << endl
             << "q. Quit" << endl << spacer << endl;

        cin >> choice;

        switch(choice)
        {
            case '1':
                cout << "Enter 'l' to shift left, or 'r' to shift to the right: ";
                cin >> choice;
                cout << "Number of rotations: ";
                cin >> n;
                puzzle->rotate(choice, n, false);
                break;
            case '2':
                puzzle->spin(false);
                break;
            case '3':
                delete[] puzzle;
                puzzle = new TopSpin();
                break;
            case '4': // Remove or split into diff function
                delete[] puzzle;
                cout << endl << "Number of random moves: ";
                cin >> n;
                cout << endl << "Would you like to see each move? (1) for yes, (0) for no:";
                cin >> pprint;
                puzzle = randomize_puzzle(n, pprint);

                break;
            case 'q':
                cout << "Goodbye!" << endl << endl;
                break;
            default:
                    cout << "I didn't understand that" << endl;
        }
    }
}

void treewalker()
{
    char c;
    int i, rand;
    rand = 3;
    TopSpin* ptr = randomize_puzzle(rand,false);
    Node* root = new Node(*ptr, 0, NULL, make_tuple('x','x'));
        cout << endl << "i. Info for Current Node"
             << endl << "g. Generate children for Current Node"
             << endl << "d. Switch to child"
             << endl << "u. Switch to parent"
             << endl << "n. Generate new tree"
             << endl << "s. Run IDA* (fingers crossed)"
             << endl << "t. Trace out solution"
             << endl << "p. Print this menu"
             << endl << "q. Quit"
             << endl << endl;
        cout << endl << "Enter choice: ";
        cin >> c;
    

    while(c != 'q')
    {
        switch(c)
        {
            case 'i':
                root->printNodeInfo();
                break;
            case 'g':
                root->createChildren();
                break;
            case 'd':
                cout << endl << "Child index (0-1, 0-2 for root, -1 cancel): ";
                cin >> i;
                if( i == -1 ) break;
                root = root->getChild(i);
                break;
            case 'u':
                if(root->getParent() != NULL) root = root->getParent();
                break;
            case 'n':
                cout << endl << "Enter random number of moves for puzzle (-1 to cancel): ";
                cin >> rand;
                if( rand == -1 ) break;
                ptr = randomize_puzzle(rand,false);
                root = new Node(*ptr, 0, NULL, make_tuple('x','x'));
                break;
            case 's':
                IDA(root, rand);
                break;
            case 't':
                printPath();
                break;
            case 'p':
                cout << endl << "i. Info for Current Node"
                     << endl << "g. Generate children for Current Node"
                     << endl << "d. Switch to child"
                     << endl << "u. Switch to parent"
                     << endl << "n. Generate new tree"
                     << endl << "s. Run IDA* (fingers crossed)"
                     << endl << "t. Trace out solution"
                     << endl << "p. Print this menu"
                     << endl << "q. Quit"
                     << endl << endl;
                break;
            default:
                break;             
        } 
        cout << ">";
        cin >> c;
    }
}

int main()
{
    //menu();
    treewalker();    
    return 0;
}
