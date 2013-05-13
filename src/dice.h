//File: dice.h
//Author: Jeremy Reed
//Date: 5-26-2008
//Contributors: NONE
//Purpose: rolls an n-sided die.  The parameter n is given as input.
//

/*
Copyright (C) 2013 Jeremy Reed

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
