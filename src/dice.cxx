//File:   dice.cxx
//Author: Jeremy Reed 
//Date:   5-26-2008
//Contributors: NONE
//Purpose:
//Revisions:
//
//         $Log$

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
