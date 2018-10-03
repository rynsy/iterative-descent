#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include "topspin.h"
#include "randomizer.h"

using namespace std;
/*
 *  As input, this function takes int n (a number of random
 *  moves to make) and bool pprint (a flag for displaying
 *  each of the moves the randomizer makes).
 *
 *  The function creates a pointer to a new instance of the
 *  TopSpin puzzle data-structure, and uses the Mersenne Twister
 *  data-structure to generate random numbers to make decisions.
 */
TopSpin* randomize_puzzle(int n, bool pprint)
{

  mt19937 mt_rand(time(0));
  TopSpin* puzzle = new TopSpin();
  int i, num, rotate = 0;
  bool spun;               //used to indicate if we've 'spun' the wheel
  char cur_dir, dir;

  if(mt_rand() % 2 == 0) spun = true; //pick a start state for spun
  else spun = false;

  while(n-- > 0)
  {
    /*
     * I use spun to prevent multiple spins of the wheel in a row,
     * but just using that in the condition causes the randomizer
     * to alternate between "spin" and "rotate", to encourage more
     * rotations in a row I added a check to see if a random number is
     * odd, and rotate if that's the case.
     */
    if(spun || (mt_rand() % 2 == 1))
    {
      num = mt_rand();
      if(num % 2 == 0) //Let's just say even means go left
          dir = 'l';
      else
          dir = 'r';

      if(((rotate+1) >= 20) || ((dir != cur_dir) && (rotate > 0)))
      {
          /* If you're trying to rotate too far in a direction,
           * or if you've rotated in a direction but you're trying
           * to change directions, you should probably just spin
           * the wheel.
           * */
          puzzle->spin(pprint);
          spun = true;
          rotate = 0;
      } else if( dir != cur_dir && (rotate == 0) )
      { /*
         * If you've changed directions, but haven't rotated, that's
         * okay. Just update current direction.
         * */
        cur_dir = dir;
        puzzle->rotate(dir, 1, pprint);
        spun = false;
        rotate++;
      } else //Everything's good, rotate.
      {
          puzzle->rotate(dir, 1, pprint);
          rotate++;
          spun = false;
      }
    }
    else
    {
      puzzle->spin(pprint);
      spun = true;
      rotate = 0;
    }
  }

  return puzzle;
}
