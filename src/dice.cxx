//File:    $Id$
//Author: Jeremy Reed
//Date:
//Contributors: NONE
//Purpose:
//Revisions:
//
//         $Log$
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


#include <iostream>
#include "dice.h"

using namespace std;


namespace DICE
{


/////////////////////////////////////////////////////////////////////


   dice::dice()
   {
      cout << "dice::dice() called." << endl << endl;
      srand( time( 0 ) );
      result = 0;
   }


/////////////////////////////////////////////////////////////////////


   dice::~dice()
   {
      cout << "dice::~dice() called." << endl << endl;
   }

   int
   dice::roll( int N )
   {

      if( N > 0 )
      {
         result = 1 + ( rand() % N );
      }
      else
      {
         cout << "N cannot be 0 or negative!" << endl << endl;
         result = 0;
      }
      return( result );
   }

   int
   dice::roll( int N, int X )
   {
      result = 0;

      if ( N > 0 )
      {
         for ( int i = 0 ; i != X ; i++ )
         {
            result = result + roll( N );
         }
      }
      else
      {
         cout << "N cannot be 0 or negative!" << endl << endl;
         result = 0;
      }
      return( result ); 
   }

   int
   dice::roll_range( int start, int end )
   {
      start = start - 1;

      if ( ( start > 0 ) && ( end > 0 ) && ( start < end ) )
      {
         result = start + roll( end - start );
      }
      else
      {
         cout << "Both start and end cannot be 0 or negative!" << endl << endl;
         result = 0;
      }
      return result;
   } 

/////////////////////////////////////////////////////////////////////


}
