//File: dice.h
//Author: Jeremy Reed
//Date: 5-26-2008
//Contributors: NONE
//Purpose: rolls an n-sided die.  The parameter n is given as input.
//

#if !defined __DICE_H
#define __DICE_H

#include <iostream>
#include <stdlib.h>
#include <time.h>

namespace DICE
{
   class dice
   {

      public:  // Typedefs and public constants.


      private: // Data members

         int n;
         int result;

      public:  // Constructors and destructors

         dice();
         ~dice();

      private: // Special functions.

      public:  // Member functions

         int roll( int N );
         int roll( int N, int X);  // rolls a N sided die X times, returns
                                   // the sum. 
         int roll_range( int start, int end );  // Random number in the range of
                                                // [ start ... end ]

   }; // End class
}

#endif
