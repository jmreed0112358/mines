// Name Jeremy Reed 
// Email: jeremyr@colorado.edu
// Date: 11-17-2009
// File: main.cxx
// Purpose: Plays a game of minesweeper.
// Purpose: Modified version of the vsetexam.cxx file given out with
//          the assignment.
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

/* Something interesting. */


#include <iostream>   // Provides cout, cin
#ifdef __Darwin__
#include <sys/malloc.h>   // Provides memory management functions.
#endif
#ifdef __Linux__
#include <malloc.h>
#endif
#ifdef __FreeBSD__
#include <stdlib.c>
#endif
#include <string.h>   // Provides C - style string functions.
#include <cctype>     // Provides toupper.
#include <iomanip>    // Provides setw to set the width of an output.
#include <cstdlib>    // Provides EXIT_SUCCESS.
#include "dice.h"     // Provides the Dice class.

// Constant values for Easy, Medium, and Hard puzzles.
#define E_ROW 10 
#define E_COL 10
#define E_N 10
#define M_ROW 30
#define M_COL 20
#define M_N 40
#define H_ROW 40
#define H_COL 40
#define H_N 200

using namespace std;
using namespace DICE;

//-----------------------------------------------------------------------------
// PROTOTYPES of functions used in this program:

int clear_square( int** data, int** mask, int row, int col, int x, int y );
// Preconditions: row and col must be positive.  x and y must be postive, 
//                y < row, and x < col.
// Postcondition: The requested square has been cleared.  
//                There are three possible return values.
//                This function returns -1 if the input is invalid.
//                This function returns 0 if there was no error.
//                This function returns 1 if a mine has been uncovered.
//                If the square has already been cleared, this function
//                does nothing, and returns 0.

int clear_neighbor( int** data, int** mask, int** viewed, int row, int col, 
                    int x, int y );
// Preconditions: row and col must be positive.  x and y must be positive,
//                y < row, and x < col.
//                Values for dir: No diagonals!
//                0: up.
//                1: left.
//                2: down.
//                3: right.
//
// Postconditions: Squares have been cleared in the given direction, stopping
//                 only when we reach a square holding a postive, non-zero 
//                 value.
//                 This function will be a recursive function,
//                 with a stopping case being a square w/ a postive, non-zero
//                 value.

void delete_dynamic_array( int**& data, int row );
// Postcondition: Frees up dynamic memory.

int game_win( int** data, int** mask, int row, int col, int n );

int place_flag( int** data, int** mask, int row, int col, int x, int y,
                int& flagged );
// Preconditions: row and col must be positive.  x and y must be postive, 
//                y < row, and x < col.
// Postcondition: The requested square has been cleared.  
//                There are three possible return values.
//                This function returns -1 if the input is invalid.
//                This function returns 0 if there was no error.
//                This function returns 1 if the square has already been 
//                flagged.

int place_mines( dice* die, int**& data, int row, int col, int n );
// Preconditions: row and col must be positive.  n must be less than or equal
//                to ( row * col ).  Otherwise we return -1, and data remains
//                unchanged.
// Postconditions: Return values are described in the precondition.  If there
//                 is no error, data is modifified to contain mines,
//                 and all locations adjacent to mines have a numerical value
//                 indicating how many mines are adjacent.

int play_game( int**& data, int**& mask, int row, int col, int n );
// Preconditions: both data, and mask are valid arrays.  row and col are
//                positive.
// Postconditions: A game of minesweeper has been played.
//                 The return value indicates the outcome of the game.
//                 TODO: Should change this return value to include
//                 the length of time it took to play the game.
//                 This feature isn't so important for a text-based version,
//                 but will be needed for a graphical version.

void print_menu( );
// Postcondition: A menu of choices for this program has been written to cout.
// Library facilties used: iostream.h

void print_game_menu( );
// Postcondition: A menu has been printed to the screen.  This is a sub-menu.

void print_game( int** data, int** mask, int row, int col );
// Postcondition: The game's state has been printed to the screen.
//                This function uses the mask to determinate what can be
//                shown to the player.

void print_puzzle( int** data, int row, int col );
// Postcondition: This function prints the puzzle to the screen.
//                The mask is not used at all, so all information
//                may be viewed by the player.

int get_int( );
// Postcondition: An integer has been read in from input.

char get_user_command( );
// Postcondition: The user has been prompted to enter a one character command.
// A line of input (with at least one character) has been read, and the first
// character of the input line is returned.

double get_number( );
// Postcondition: The user has been prompted to enter a real number. The
// number has been read, echoed to the screen, and returned by the function.

unsigned int get_unsigned_int( );
// Postcondition: An unsigned int has been read in from input.

int make_dynamic_array( int**& data, int row, int col );

//-----------------------------------------------------------------------------


// **************************************************************************
// Credit for these new/delete replacements:  Professor Main.
// Replacements for new and delete:
// The next two functions replace the new and delete operators. Any code
// that is linked with this .cxx file will use these replacements instead
// of the standard new and delete. The replacements provide three features:
// 1. The global variable memory_used_now keeps track of how much memory has
//    been allocated by calls to new. (The global variable is static so that
//    it cannot be accessed outside of this .cxx file.)
// 2. The new operator fills all newly allocated memory with a GARBAGE char.
// 3. Each block of newly allocated memory is preceeded and followed by a
//    border of BORDER_SIZE characters. The first part of the front border
//    contains a copy of the size of the allocated memory. The rest of the
//    border contains a BORDER char.
// During any delete operation, the border characters are checked. If any
// border character has been changed from BORDER to something else, then an
// error message is printed and the program is halted. This stops most
// cases of writing beyond the ends of the allocated memory.
// **************************************************************************

//-----------------------------------------------------------------------------
// GLOBALS used by new/delete.
//-----------------------------------------------------------------------------

const  size_t BORDER_SIZE     = 2*sizeof(double);
const  char   GARBAGE         = 'g';
const  char   BORDER          = 'b';
static size_t memory_used_now = 0;

//-----------------------------------------------------------------------------

void* operator new(size_t size)
{
    char   *whole_block;   // Pointer to the entire block that we get from heap
    size_t *size_spot;     // Spot in the block where to store a copy of size
    char   *front_border;  // The border bytes in front of the user's memory 
    char   *middle;        // The memory to be given to the calling program
    char   *back_border;   // The border bytes at the back of the user's memory
    size_t i;              // Loop control variable

    // Allocate the block of memory for the user and for the two borders.
    whole_block = (char *) malloc(2*BORDER_SIZE + size);
    if (whole_block == NULL)
    {
        cout << "Insufficient memory for a call to the new operator." << endl;
        exit(0);
    }

    // Figure out the start points of the various pieces of the block.
    size_spot = (size_t *) whole_block;
    front_border = (char *) (whole_block + sizeof(size_t));
    middle = (char *) (whole_block + BORDER_SIZE);
    back_border = middle + size;

    // Put a copy of the size at the start of the block.
    *size_spot = size;

    // Fill the borders and the middle section.
    for (i = 0; i < BORDER_SIZE - sizeof(size_t); i++)
        front_border[i] = BORDER;
    for (i = 0; i < size; i++)
        middle[i] = GARBAGE;
    for (i = 0; i < BORDER_SIZE; i++)
        back_border[i] = BORDER;

    // Update the global static variable showing how much memory is now used.
    memory_used_now += size;
    
    return middle;
}

//-----------------------------------------------------------------------------

void operator delete(void* p)
{
    char   *whole_block;   // Pointer to the entire block that we get from heap
    size_t *size_spot;     // Spot in the block where to store a copy of size
    char   *front_border;  // The border bytes in front of the user's memory 
    char   *middle;        // The memory to be given to the calling program
    char   *back_border;   // The border bytes at the back of the user's memory
    size_t i;              // Loop control variable
    size_t size;           // Size of the block being returned
    bool   corrupt;        // Set to true if the border was corrupted

    // Figure out the start of the pieces of the block, and the size.
    whole_block = ((char *) (p)) - BORDER_SIZE;
    size_spot = (size_t *) whole_block;
    size = *size_spot;
    front_border = (char *) (whole_block + sizeof(size_t));
    middle = (char *) (whole_block + BORDER_SIZE);
    back_border = middle + size;

    // Check the borders for the BORDER character.
    corrupt = false;
    for (i = 0; i < BORDER_SIZE - sizeof(size_t); i++)
        if (front_border[i] != BORDER)
            corrupt = true;
    for (i = 0; i < BORDER_SIZE; i++)
        if (back_border[i] != BORDER)
            corrupt = true;

    if (corrupt)
    {
        cout << "The delete operator has detected that the program wrote\n";
        cout << "beyond the ends of a block of memory that was allocated\n";
        cout << "by the new operator. Program will be halted." << endl;
        exit(0);
    }
    else
    {
        // Fill memory with garbage in case program tries to use it
        // even after the delete.
        for (i = 0; i < size + 2*BORDER_SIZE; i++)
            whole_block[i] = GARBAGE;
        free(whole_block);
        memory_used_now -= size;
    }
    
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int clear_square( int** data, int** mask, int row, int col, int x, int y )
{

   int** visited = NULL;  // Keep track of where we've already been.

   cout << "clear_square(...) called." << endl;

   cout << "x: " << x << ", y: " << y << endl;

   // Bounds check.
   if ( ( x < 0 ) || ( y < 0 ) || ( y >= row ) || ( x >= col ) )
   {
      return -1;
   }

   cout << "mask[y][x]: " << mask[y][x] << endl;

   if ( mask[y][x] == 1 )
   {
      // The square has already been cleared.
      return 0;
   }
   else if ( mask[y][x] == -1 )
   {
      // Shouldn't be able to clear a square that is already flagged.
      // The user should clear the flag first before attempting to clear
      // the square.
      return 0;
   }
   else
   {
      if ( data[y][x] == -1 )
      {
         // Oops, just hit a mine!
         return 1;
      }
      else if ( data[y][x] > 0 )
      {
         mask[y][x] = 1;
      }
      else
      {
         // Now we allocate memory to the visited array.
         make_dynamic_array( visited, row, col );

         // Clear the square.
         mask[y][x] = 1;
         visited[y][x] = 1;

         // Now we need to clear the neighbors!

         // Spawn calls in all 8 directions!
         clear_neighbor( data, mask, visited, row, col, (x-1), y );
         clear_neighbor( data, mask, visited, row, col, x, (y-1) );
         clear_neighbor( data, mask, visited, row, col, (x+1), y );
         clear_neighbor( data, mask, visited, row, col, x, (y+1) );
         clear_neighbor( data, mask, visited, row, col, (x-1), (y-1) );
         clear_neighbor( data, mask, visited, row, col, (x-1), (y+1) );
         clear_neighbor( data, mask, visited, row, col, (x+1), (y-1) );
         clear_neighbor( data, mask, visited, row, col, (x+1), (y+1) );

         // Deallocate memory reserved for the visited array.
         delete_dynamic_array( visited, row );

         cout << "Done!" << endl;

      }
   }

   return 0;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int clear_neighbor( int** puzzle, int** mask, int** viewed, int row, int col,
                    int x, int y )
{

   // Bounds check.
   // Bounds check.
   if ( ( x < 0 ) || ( y < 0 ) || ( y >= row ) || ( x >= col ) )
   {
      return -1;
   }

   // Base case
   if ( ( puzzle[y][x] != 0 ) || ( viewed[y][x] != 0 ) )
   {
      if ( viewed[y][x] == 0 )
      {
         if ( puzzle[y][x] != -1 )
         {
            mask[y][x] = 1;
            viewed[y][x] = 1;
         }
      }
   }
   else
   {
      // Recursive case.
      mask[y][x] = 1;
      viewed[y][x] = 1;
      clear_neighbor( puzzle, mask, viewed, row, col, (x-1), y );
      clear_neighbor( puzzle, mask, viewed, row, col, x, (y-1) );
      clear_neighbor( puzzle, mask, viewed, row, col, (x+1), y );
      clear_neighbor( puzzle, mask, viewed, row, col, x, (y+1) );
      clear_neighbor( puzzle, mask, viewed, row, col, (x-1), (y-1) );
      clear_neighbor( puzzle, mask, viewed, row, col, (x-1), (y+1) );
      clear_neighbor( puzzle, mask, viewed, row, col, (x+1), (y-1) );
      clear_neighbor( puzzle, mask, viewed, row, col, (x+1), (y+1) );
   }

   return 0;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void delete_dynamic_array( int**& data, int row )
{
   cout << "void delete_dynamic_array( ... ) called." << endl;
   int i;

   for( i = 0 ; i < row ; ++i )
   {
      delete [ ] data[i];
   }

   delete [] data;
   data = NULL;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int game_win( int** data, int** mask, int row, int col, int n )
{

   int z = 0;

   for ( int i = 0 ; i != row ; i++ )
   {
      for ( int j = 0 ; j != col ; j++ )
      {
         if ( data[i][j] == -1 )
         {
            if ( mask[i][j] != -1 )
            {
               return 0;
            }
            else
            {
               z++;
            }
         }
      }
   }

   if ( z != n )
   {
      return 0;
   }
   else
   {
      return 1;
   }
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int place_flag( int** puzzle, int** mask, int row, int col, int x, int y,
                int& flagged )
{

   cout << "row: " << row << endl
        << "col: " << col << endl
        << "x:   " << x << endl
        << "y:   " << y << endl << endl;

   if ( ( x < 0 ) || ( y < 0 ) || ( y >= row ) || ( x >= col ) )
   {
      return -1;
   }

   if ( mask[y][x] == -1 )
   {
      mask[y][x] = 0;
      flagged--;
   }
   else if ( mask[y][x] == 1 )
   {
      return 1;
   }
   else
   {
      mask[y][x] = -1;
      flagged++;
   }

   return 0;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int place_mines( dice* die, int**& data, int row, int col, int n )
{

   cout << "place_mines called!" << endl;

   int x = 0;
   int y = 0;
   double z = ( (double) n / (double) ( row*col ) );
   int r = 0;

   if ( n > (row*col) )
   {
      return -1; 
   }

   // Check sparseness of minefield.
   cout << "Percentage mined: " << setprecision( 3 ) << z  << " %" << endl;
  
   // Initialize data to 0, randomly insert mines.
   for ( int i = 0 ; i != n ; i++ )
   {
      do
      {
         x = ( die->roll( col ) ) - 1;
         y = ( die->roll( row ) ) - 1;
         r = r + 1;
      }
      while( (int) data[y][x] == -1 );

      data[y][x] = -1;

      if ( y != ( row - 1 ) && ( data[y+1][x] != -1 ) )  
      {
         (data[y+1][x])++;
      }

      if ( y != 0  && ( data[y-1][x] != -1 ) )
      {
         (data[y-1][x])++;
      }

      if ( x != ( col - 1 )  && ( data[y][x+1] != -1 ) )
      {
         (data[y][x+1])++;
      }

      if ( x != 0  && ( data[y][x-1] != -1 ) )
      {
         (data[y][x-1])++;
      }

      if ( ( y != ( row - 1 ) ) && ( x != ( col - 1 ) )  
           && ( data[y+1][x+1] != -1 ) )
      {
         (data[y+1][x+1])++;
      }
 
      if ( ( y != ( row -1 ) ) && ( x != 0 )  && ( data[y+1][x-1] != -1 ) )
      {
         (data[y+1][x-1])++;
      }

      if ( ( y != 0 ) && ( x != ( col -1 ) )  && ( data[y-1][x+1] != -1 ) )
      {
         (data[y-1][x+1])++;
      }

      if ( ( y != 0 ) && ( x != 0 )  && ( data[y-1][x-1] != -1 ) )
      {
         (data[y-1][x-1])++;
      } 
   }

   cout << "It took " << r << " attempts to place " << n << " mines." << endl;
   cout << "Done placing mines!" << endl;

   return 0;
} 

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int play_game( int**& data, int**& mask, int row, int col, int n )
{

    int retval = 0;
    int input1 = 0;
    int input2 = 0;
    int flagged = 0;
    char choice;              // A command character entered by the user

    do
    {

        if ( game_win( data, mask, row, col, n ) )
        {
           cout << "You've found all the mines!" << endl;
           return 0;
        }
        else
        { 

        cout << endl;
        cout << "You have " << ( n - flagged ) << " flags left to place."
             << endl;
        print_game( data, mask, row, col );
        print_game_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
           
           case 'P':
              cout << "Printing the puzzle layer!" << endl << endl;
              print_puzzle( data, row, col );
              break;
           case 'F':
              cout << "Placing/Clearing a flag!" << endl;
              cout << "Give me a square!" << endl;
              cout << "x: ";
              input1 = get_int( );
              cout << "y: ";
              input2 = get_int( );
              while( ( retval = place_flag( data, mask, row, col, input1, input2,
                                            flagged ) ) )
              {
 
                 if ( retval != 1 )
                 {
                    cout << "retval: " << retval << endl;
                    cout << "Bad input!  Try again!" << endl;
                    cout << "x: ";
                    input1 = get_int( );
                    cout << "y: ";
                    input2 = get_int( );
                 }
                 else
                 {
                    cout << "You cannot place a flag here!" << endl;
		    break;
                 }
              }
              break;
           case 'C':
              cout << "Clearing a square!" << endl;
              cout << "Give me a square!" << endl;
              cout << "x: ";
              input1 = get_int( );
              cout << "y: ";
              input2 = get_int( );
              while( ( retval = clear_square( data, mask, row, col, 
                                              input1, input2 ) ) != 0 )
              {
                 if ( retval != 1 )
                 {
                    cout << "Bad input!  Try again!" << endl;
                    cout << "x: ";
                    input1 = get_int( );
                    cout << "y: ";
                    input2 = get_int( );
                 }
                 else
                 {
                    cout << endl << endl << "Boom!  You hit a mine!" << endl
                         << "GAME OVER!!!" << endl << endl;
                    print_puzzle( data, row, col );
                    return 1;
                 }
              }
              break;
           case 'Q':
              cout << "Returning to main menu." << endl;
              break;
           default:
              cout << choice << " is invalid. Sorry." << endl;
              break;
        }
        }
    }
    while (choice != 'Q');

   return 0;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void print_menu( )
{
    cout << endl;
    cout << "The following choices are available: " << endl;
    cout << " E  Easy difficulty." << endl;
    cout << " M  Medium difficulty." << endl;
    cout << " H  Hard difficulty." << endl;
    cout << " C  Custom difficulty." << endl;
    cout << " Q  Quit this test program" << endl;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void print_game_menu( )
{
   cout << endl;
   cout << "Player, choose your action!" << endl;
   cout << " P  Print Puzzle layer." << endl;
   cout << " F  Place/Clear a flag." << endl;
   cout << " C  Select a square to uncover." << endl;
   cout << " Q  Quit the game!" << endl;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void print_game( int** data, int** mask, int row, int col )
{
   for ( int i = 0 ; i != row ; i++ )
   {
      for ( int j = 0 ; j != col ; j++ )
      {
         if ( mask[i][j] == 1 )
         {
            if ( data[i][j] > 0 )
            {
               cout << data[i][j];
            }
            else if ( data[i][j] == 0 )
            {
               cout << ".";
            }
            else
            {
               cout << "m";
            }
         }
         else if ( mask[i][j] == -1 )
         {
            cout << "f";
         }
         else
         {
            cout << "#";
         }
      }
      cout << endl;
   } 
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void print_puzzle( int** data, int row, int col )
{
   for ( int i = 0 ; i != row ; i++ )
   {
      for ( int j = 0 ; j != col ; j++ )
      {
         if ( data[i][j] > 0 )
         {
            cout << data[i][j];
         }
         else if ( data[i][j] == 0 )
         {
            cout << ".";
         }
         else
         {
            cout << "m";
         }
      }
      cout << endl;
   }
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
int get_int( )
// Library facilties used: iostream.h
{
    int result;

    cout << "Please enter an integer : ";
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
char get_user_command( )
// Library facilties used: iostream.h
{
    char command;

    cout << "Enter choice: ";
    cin >> command;

    return command;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
double get_number( )
// Library facilties used: iostream.h
{
    double result;

    cout << "Please enter the next real number for the sequence: ";
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
unsigned int get_unsigned_int( )
// Library facilties used: iostream.h
{
    unsigned int result;

    cout << "Please enter an unsigned integer : ";
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}
//-----------------------------------------------------------------------------

int make_dynamic_array( int**& data, int row, int col )
{
   int i,j;
                                   // Avoid using the global temp ptr.
   if ( row == 0 || col == 0 )
   {
      cout << "Cannot have one dimension equal to zero," << endl
           << "and have the other equal to a non-zero number. """
           << endl << endl;
      return -1;
   }
   else 
   {

      if ( row > 0 && col > 0 )
      {
         data = new int*[ row ];
         for ( i = 0 ; i < row ; i++ )
         {
            data[ i ] = new int[ col ];

         }

         for ( i = 0 ; i != row ; i++ )
         {
            for ( j = 0 ; j != col ; j++ )
            {
               data[i][j] = 0;
            }
         }
      }
      else
      {
         cout << "Cannot have negative values for rows and columns!"
              << endl
              << "Doing nothing!"
              << endl << endl;
         return -1;
      }
   }
   return 0;
}


//----------------------------------------------------------------------------- 
int main( )
{
    dice die;          // Our random number generator.
    dice* die_ptr = &die;
    char choice = '0'; // A command character entered by the user
    int n = 0;    // Number of mines to use in this puzzle.
    int x = 0;
    int y = 0;
    int** puzzle;    //  -1, if there is a mine.
                        //   0, if this space is not adjacent to a mine.
                        // 1-9, if this space is adjacent to 1-9 mines.
    int** mask;      // Determines if the location is uncovered.
                        // given location.


    do
    {
        cout << endl;
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
        case 'E':
            cout << "Playing an easy puzzle!" << endl;
            make_dynamic_array( puzzle, E_ROW, E_COL );
            make_dynamic_array( mask, E_ROW, E_COL );
            place_mines( die_ptr, puzzle, E_ROW, E_COL, E_N );
            play_game( puzzle, mask, E_ROW, E_COL, E_N );
            delete_dynamic_array( puzzle, E_ROW );
            delete_dynamic_array( mask, E_ROW );
            break;
        case 'M':
            cout << "Playing a medium puzzle!" << endl;
            make_dynamic_array( puzzle, M_ROW, M_COL );
            make_dynamic_array( mask, M_ROW, M_COL );
            place_mines( die_ptr, puzzle, M_ROW, M_COL, M_N );
            play_game( puzzle, mask, M_ROW, M_COL, M_N );
            delete_dynamic_array( puzzle, M_ROW );
            delete_dynamic_array( mask, M_ROW );
            break;
        case 'H':
            cout << "Playing a hard puzzle!" << endl;
            make_dynamic_array( puzzle, H_ROW, H_COL );
            make_dynamic_array( mask, H_ROW, H_COL );
            place_mines( die_ptr, puzzle, H_ROW, H_COL, H_N );
            play_game( puzzle, mask, H_ROW, H_COL, H_N );
            delete_dynamic_array( puzzle, H_ROW );
            delete_dynamic_array( mask, H_ROW );
            break;
        case 'C':
            cout << "Set up a custom puzzle." << endl;
            cout << "Number of columns: ";
            x = get_int( );
            cout << "Number of rows: ";
            y = get_int( );
            cout << "Number of mines: ";
            n = get_int( );

            while( ( x < 0 ) || ( y < 0 ) || ( n > ( y * x ) ) )
            {
               cout << "Bad input!  Try again!" << endl;
               cout << "Number of columns: ";
               x = get_int( );
               cout << "Number of rows: ";
               y = get_int( );
               cout << "Number of mines: ";
               n = get_int( );
            }

            make_dynamic_array( puzzle, y, x );
            make_dynamic_array( mask, y, x );
            place_mines( die_ptr, puzzle, y, x, n );
            play_game( puzzle, mask, y, x, n );
            delete_dynamic_array( puzzle, y );
            delete_dynamic_array( mask, y );

            break;
        case 'Q':
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << choice << " is invalid. Sorry." << endl;
            break;
        }
    }
    while (choice != 'Q');

    return EXIT_SUCCESS;
}
