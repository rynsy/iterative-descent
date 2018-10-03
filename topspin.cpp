#include <iostream>
#include <string>
#include "topspin.h"

using namespace std;

TopSpin::TopSpin()
{
    /*  I leave l_ptr and r_ptr as constants, and swap the values
     *  of the array around to "rotate"
     */
  l_ptr = 0;
  r_ptr = 3;
  for(int i = 0; i < 20; i++)
  {
    seq[i] = i;
  }
}

TopSpin::TopSpin(volatile TopSpin& ancestor)
{
    l_ptr = ancestor.l_ptr;
    r_ptr = ancestor.r_ptr;

    for(int i = 0; i < 20; i++)
    {
        seq[i] = ancestor.seq[i];
    }
}

/* Takes as input a char d, an int r, and a bool pprint.
 * d indicates the direction to rotate, r indicates how
 * many times. pprint is used to print out a screen showing
 * the state of the puzzle after the rotation.
 */
void TopSpin::rotate( char d, int r, bool pprint)
{
  string sep(20,'#');

  for(int i = 0; i < r; i++)
  {
    if( d == 'r' )
    {
        l_ptr = (l_ptr + 1) % 20;
        r_ptr = (r_ptr + 1) % 20;
    }
    else if( d == 'l' )
    {
        l_ptr = (l_ptr - 1) % 20;
        r_ptr = (r_ptr - 1) % 20;

        if(l_ptr < 0)
            l_ptr = 20 + l_ptr;
        if(r_ptr < 0)
            r_ptr = 20 + r_ptr;
    }
  }

  if(pprint)
  {
    cout << sep << endl;
    cout << "Just rotated the wheel " << r << " times to the ";

    if(d == 'l') cout << "left" << endl;
    else cout << "right" << endl;
    cout << sep << endl;
    print();

  }
}

/*  The function uses swap to "spin" the wheel by exchanging
 * the values stored in the indicies between l_ptr and r_ptr.
 *
 * bool pprint is used to print the state of the puzzle after
 * the spin
 */
void TopSpin::spin(bool pprint)
{
  string sep(20,'#');
 
  if( r_ptr != 0 && r_ptr != 2 ) {
    for( int i = 0; i <= 1; i++ )
    {
        swap(l_ptr + i, r_ptr - i);
    } 
  } else {
    if( r_ptr == 2 ){
        swap(l_ptr, r_ptr);
        swap(r_ptr-2, r_ptr-1);
    } //These are my edge cases
    if (r_ptr == 0) {
        swap(l_ptr, r_ptr);
        swap(l_ptr+1, l_ptr+2);
    }
  }
  if(pprint)
  {
    cout << sep << endl;
    cout << "Just spun the wheel" << endl;
    cout << sep << endl;
    print();

  }
}

/*
 *  Helper function for spin. Exchanges the values stored in the
 *  array at indicies i and j.
 */
void TopSpin::swap(int i, int j)
{
  int temp;
  temp = seq[i];
  seq[i] = seq[j];
  seq[j] = temp;
}

int TopSpin::heuristicValue()
{
    int butterknife, hypotheticSpin;
    butterknife = butterknifeValue();
    spin(false);
    hypotheticSpin = butterknifeValue() + 1;
    spin(false);
    if(hypotheticSpin < butterknife)
        return hypotheticSpin;
    else
        return butterknife;
}

int TopSpin::butterknifeValue()
{
    int dist[20];
    int h1, h2, max=0;
    for(int i = 0; i < 20; i++)
    {
        h1 = abs(seq[i] - i);
        h2 = 20 - h1;
        if( h1 < h2 )
            dist[i] = h1;
        else
            dist[i] = h2;
    }
    for(int i = 0; i < 20; i++)
    {
        if(dist[i] > max)
            max = dist[i];
    }
    return max;
}

bool TopSpin::solved()
{   
    int result = 0;
    result = heuristicValue();
    return result == 0;
}

/*
 * Prints out the state of the puzzle with '^'s pointing at the
 * values that l_ptr and r_ptr are pointing at.
 *
 */
void TopSpin::print()
{
  string spacer(20, '#');

  //cout << spacer << endl;

  for(int i = 0; i < 20; i++)
  {
    cout << " " << seq[i];
  }
  cout << endl << " ";
  for(int i = 0; i < 20; i++)
  {
    if( i == l_ptr || i == r_ptr) {
       cout << "^";  
       if(seq[i] >= 10)
          cout << "  ";
       else
          cout << " ";
    }
    else{
    if(seq[i] >= 10)
      cout << "   ";
    else
      cout << "  ";
    }
  }
  cout << endl;// << spacer;
}
