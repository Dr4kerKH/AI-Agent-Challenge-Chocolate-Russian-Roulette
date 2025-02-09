// CS 4318, spring 2024
// Agent Challenge 5: Chocolate Russian roulette
//
// Here's an example agent function.  You can do much better than this.

#include "crr.h"

ChocolateSquareLocation crrAgentNibbleTop(const ChocolateBar &bar)
{
   // Find the topmost single available square.
   ChocolateSquareLocation bite;
   int biteColumn, biteRow;

   // Consider each possible bite, starting with the top row.
   for (biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1)
   {
      for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1)
      {
         // If a valid bite is found, return it.
         bite = ChocolateSquareLocation(biteColumn, biteRow);
         if (bar.isSquareThere(bite))
         {
            return bite;
         }
      }
   }

   // If nothing's left, bite the poison square.
   return ChocolateSquareLocation(0, 0);
}
