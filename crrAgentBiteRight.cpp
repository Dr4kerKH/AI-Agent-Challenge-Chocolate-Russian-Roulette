// CS 4318, spring 2024
// Agent Challenge 5: Chocolate Russian roulette
//
// Here's an example agent function.  You can do much better than this.

#include "crr.h"

ChocolateSquareLocation crrAgentBiteRight(const ChocolateBar &bar)
{
   // Find the entire rightmost available column of squares.
   ChocolateSquareLocation bite;
   int biteColumn;

   // Consider each possible bite, starting with the right column.
   for (biteColumn = bar.getWidth() - 1; biteColumn > 0; biteColumn -= 1)
   {
      // If a valid bite is found, return it.
      bite = ChocolateSquareLocation(biteColumn, 0);
      if (bar.isSquareThere(bite))
      {
         return bite;
      }
   }

   // If only the left column remains, try to bite all but the poison square.
   bite = ChocolateSquareLocation(0, 1);
   if (bar.isSquareThere(bite))
   {
      return bite;
   }

   // If nothing's left, bite the poison square.
   return ChocolateSquareLocation(0, 0);
}
