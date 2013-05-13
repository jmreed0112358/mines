//File:   dice.cxx
//Author: Jeremy Reed 
//Date:   5-26-2008
//Contributors: NONE
//Purpose:
//Revisions:
//
//         $Log$

/*
Copyright (C) yyyy  name of author

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

/////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////

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
