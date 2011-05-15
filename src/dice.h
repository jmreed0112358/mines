//File: dice.h
//Author: Jeremy Reed
//Date: 5-26-2008
//Contributors: NONE
//Purpose: rolls an n-sided die.  The parameter n is given as input.
//
// COPYRIGHT:
/*
 *
 * Copyright (c) 2011, Jeremy M. Reed
 * All rights reserved.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY Jeremy M Reed ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Jeremy M. Reed BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
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
