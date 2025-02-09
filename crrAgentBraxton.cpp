// YOUR NAME: Sonpaorong Muchhim
//
// CS 4318, spring 2024
// Agent Challenge 5: Chocolate Russian roulette

//	nice bash crrBuild.bash
//  nice ./crrRunSim

#include "crr.h"
namespace
{
// Function for Calculation of Square taken
int calSquareTaken(const ChocolateBar &bar, const ChocolateBar &newBar, bool isMaxiPlayer) {
	int	before, after, biteColumn, biteRow;
	before = after = 0;
	// If maxi player, return square taken as positive
	if (isMaxiPlayer) {
		for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1) {
			for (biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1) {
				if (bar.isSquareThere(biteColumn, biteRow))
					before++;
				if (newBar.isSquareThere(biteColumn, biteRow))
					after++;
			}
		}
		return before - after;
	}
	else { // else, min player, return square taken as negative
		for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1) {
			for (biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1) {
				if (bar.isSquareThere(biteColumn, biteRow))
					before++;
				if (newBar.isSquareThere(biteColumn, biteRow))
					after++;
			}
		}
		return -(before - after);
	}
}
// Function get remaining width of passing col
int getRemainingWidth(const ChocolateBar &bar, const int col) {
	int remain = 0;	
	for (int x = bar.getWidth() - 1; x >= 0; x -= 1) {
		if (bar.isSquareThere(x, col)) {
			remain = x;
			break;
		}
	}
	return remain;
}
// Function get remaining height of passing row
int getRemainingHeight(const ChocolateBar &bar, const int row) {
	int remain = 0;
	for (int x = bar.getHeight() - 1; x >= 0; x -= 1) {
		if (bar.isSquareThere(row, x)) {
			remain = x;
			break;
		}
	}
	return remain;
}
// MiniMax Algorithm Recurssively till return value
int value(const ChocolateBar &bar, int depth, bool isMaxiPlayer) {
	ChocolateBar newBar;
	ChocolateSquareLocation bestBite, bite;
	int bestOutcome, biteColumn, biteRow, outcome;
	int w0, h0, w1, h1;
	
	w0 = getRemainingWidth(bar, 0);
	w1 = getRemainingWidth(bar, 1);
	h0 = getRemainingHeight(bar, 0);
	h1 = getRemainingHeight(bar, 1);
	int differenceArms = abs(w0 - h0);
	
	// Terminate clause, win or lose
	if (!bar.isAnyLeft())
		return isMaxiPlayer? 1000 : -1000;
	
	// Patterns Detection
	if (!bar.isSquareThere(0, 1) && bar.isSquareThere(1, 0))
		return isMaxiPlayer? 1000 : -1000;
	if (!bar.isSquareThere(1, 0) && bar.isSquareThere(0, 1))
		return isMaxiPlayer? 1000 : -1000;
	if (!bar.isSquareThere(1, 1)) {		
		if (h0 > w0)
			return isMaxiPlayer? 1000 : -1000;
		if (h0 < w0)
			return isMaxiPlayer? 1000 : -1000;
	}
	if (bar.isSquareThere(1, 1) && differenceArms == 0)
		return isMaxiPlayer? 1000 : -1000;
	if (bar.isSquareThere(1, 1) && h0 > 2 && w0 > 2 && !bar.isSquareThere(1, 2) && !bar.isSquareThere(2, 1) && differenceArms > 1) {
		if (h0 > w0 && bar.isSquareThere(0, w0 + 2))
			return isMaxiPlayer? 1000 : -1000;
		if (h0 < w0 && bar.isSquareThere(h0 + 2, 0))
			return isMaxiPlayer? 1000 : -1000;
	}
	// More Patterns
	if (bar.isSquareThere(2, 0) && h0 - h1 == 1 && h1 > 0) 
		return isMaxiPlayer? 750:-750;
	if (!bar.isSquareThere(2, 0) && h1 > 0 && h0 - h1 >= 2) 
		return isMaxiPlayer? 750:-750;
	if (w0 == w1 && !bar.isSquareThere(0, 2) && bar.isSquareThere(w0, 1)) 
		return isMaxiPlayer? 750:-750;
	if (bar.isSquareThere(0, 2) && w0 - w1 == 1 && w1 > 0)
		return isMaxiPlayer? 750:-750;
	if (!bar.isSquareThere(0, 2) && w1 > 0 && w0 - w1 >= 2)
		return isMaxiPlayer? 750:-750;
	if (h0 == h1 && !bar.isSquareThere(2, 0) && bar.isSquareThere(1, h0)) 
		return isMaxiPlayer? 750:-750;
	
	// Depth Limit
	if (depth > 12)
		return 0;
	
	// Initialized bestOutcome
	if (isMaxiPlayer? bestOutcome = INT_MIN: bestOutcome = INT_MAX); 
	// If Maxi player
	if (isMaxiPlayer){
		for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1){
			for (biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1) {
				bite = ChocolateSquareLocation(biteColumn, biteRow);
				if (bar.isSquareThere(bite)) {
					newBar = bar;
					newBar.takeBite(bite);
					// Evaluate outcome value by recursive call minimax with increment depth
					outcome = calSquareTaken(bar, newBar, true) + value(newBar, ++depth, false);
					bestOutcome = max(bestOutcome, outcome);
				}
			}
		}
		return bestOutcome;
	}
	else { // else Min Player
		for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1){
			for (biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1) {
				bite = ChocolateSquareLocation(biteColumn, biteRow);
				if (bar.isSquareThere(bite)) {
					newBar = bar;
					newBar.takeBite(bite);
					// Evaluate outcome value by recursive call minimax with increment depth
					outcome = calSquareTaken(bar, newBar, false) + value(newBar, ++depth, true);
					bestOutcome = min(bestOutcome, outcome);
				}
			}
		}
		return bestOutcome;
	}
}
// Functio to check if the bar is full
bool isFull(const ChocolateBar &bar) {
	for (int i = bar.getWidth() - 1; i >= 0; i -= 1) {
		for (int j = bar.getHeight() - 1; j >= 0; j -= 1) {
			if (!bar.isSquareThere(i, j))
				return false;
		}
	}
	return true;
}
ChocolateSquareLocation nibbleTop(const ChocolateBar &bar) {
   // Find the topmost single available square.
   ChocolateSquareLocation bite;
   int biteColumn, biteRow;
   // Consider each possible bite, starting with the top row.
   for (biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1) {
      for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1) {
         bite = ChocolateSquareLocation(biteColumn, biteRow);
         if (bar.isSquareThere(bite))
            return bite;
      }
   }
   return ChocolateSquareLocation(0, 0);
}
}

ChocolateSquareLocation crrAgentBraxton(const ChocolateBar &bar) {
	int w0, h0, w1, h1;
	int width = bar.getWidth(), height = bar.getHeight();
	bool full = isFull(bar);
	
	// Find remaining bar in column 0,1,2
	w0 = getRemainingWidth(bar, 0);
	w1 = getRemainingWidth(bar, 1);
	// Find reminaing bar in row 0,1,2
	h0 = getRemainingHeight(bar, 0);
	h1 = getRemainingHeight(bar, 1);
	int differenceArms = abs(w0 - h0);
	
	// Win Cases:
	if (!bar.isSquareThere(0, 1) && bar.isSquareThere(1, 0))
		return ChocolateSquareLocation(1, 0);
	if (!bar.isSquareThere(1, 0) && bar.isSquareThere(0, 1))
		return ChocolateSquareLocation(0, 1);
	if (!bar.isSquareThere(1, 1)) {		
		if (h0 > w0)
			return ChocolateSquareLocation(0, h0 - differenceArms + 1);
		if (h0 < w0)
			return ChocolateSquareLocation(w0 - differenceArms + 1, 0);
	}
	if (bar.isSquareThere(1, 1) && differenceArms == 0)
		return ChocolateSquareLocation(1, 1);
	if (bar.isSquareThere(1, 1) && h0 > 2 && w0 > 2 && !bar.isSquareThere(1, 2) && !bar.isSquareThere(2, 1) && differenceArms > 1) {
		if (h0 > w0 && bar.isSquareThere(0, w0 + 2))
			return ChocolateSquareLocation(0, w0 + 2);
		if (h0 < w0 && bar.isSquareThere(h0 + 2, 0))
			return ChocolateSquareLocation(h0 + 2, 0);
	}
	
	// Setting up Cases:
	if (bar.isSquareThere(2, 0) && h0 - h1 == 1 && h1 > 0) // 2 row 1 size a part, eat 2-0 for step shape
		return ChocolateSquareLocation(2, 0);
	if (!bar.isSquareThere(2, 0) && h1 > 0 && h0 - h1 >= 2) // 2-0 gone, h0 > h1 by 2, nibble h0 by 1
		return ChocolateSquareLocation(0, h1 + 2);
	if (w0 == w1 && !bar.isSquareThere(0, 2) && bar.isSquareThere(w0, 1)) // 2column = size, nibble top right
		return ChocolateSquareLocation(w0, 1);
	
	if (bar.isSquareThere(0, 2) && w0 - w1 == 1 && w1 > 0)
		return ChocolateSquareLocation(0, 2);
	if (!bar.isSquareThere(0, 2) && w1 > 0 && w0 - w1 >= 2)
		return ChocolateSquareLocation(w1 + 2, 0);
	if (h0 == h1 && !bar.isSquareThere(2, 0) && bar.isSquareThere(1, h0)) // 2 row = size, nibble top right
		return ChocolateSquareLocation(1, h0);
	
	// ****** add more setting up
	if (h1 > 0 && !(h1 + 2 > h0) && bar.isSquareThere(0, h1+3))
		return ChocolateSquareLocation(0, h1 + 3);
	
	// Start Cases:
	if (width == 3) {
		if (full) {
			switch (height) {
				case 4: return ChocolateSquareLocation(1, 2); // 1, 2
					break;
				case 5: return ChocolateSquareLocation(2, 3); // 2, 3
					break;
				case 6:
				case 7:
				case 8: return ChocolateSquareLocation(1, 3); // 1, 3
					break;
				case 9: return ChocolateSquareLocation(1, 4); // 1, 4
					break;
			}
		}
		else if(bar.isSquareThere(1, 2) && height == 4)
			return ChocolateSquareLocation(1, 2);
	}
	if (bar.getWidth() % 2 == 0 && full) {
		if (bar.isSquareThere(3, 2))
			return ChocolateSquareLocation(3, 2);
	}
	if (bar.getWidth() % 2 == 1 && full) {
		if (bar.isSquareThere(1,2))
			return ChocolateSquareLocation(1, 2);
	}
	
	ChocolateBar newBar;
    ChocolateSquareLocation bestBite, bite;
    int bestOutcome, outcome, biteColumn, biteRow;
	bestOutcome = INT_MIN;
	// MinMax Algorithm: Max-player first bite
	for (biteColumn = width - 1; biteColumn >= 0; biteColumn -= 1) {
		for (biteRow = height - 1; biteRow >= 0; biteRow -= 1) {
			bite = ChocolateSquareLocation(biteColumn, biteRow);
			if (bar.isSquareThere(bite)) {
				newBar = bar;
				newBar.takeBite(bite);
				outcome = calSquareTaken(bar, newBar, true) + value(newBar, 1, false);
				if (outcome > bestOutcome) {
					bestBite = bite;
					bestOutcome = outcome;
				}
			}
		}
	}
	newBar = bar;
	newBar.takeBite(bestBite);
	if (!newBar.isAnyLeft())
		bestBite = nibbleTop(bar);
		
	return bestBite;
}

/*
*********************************************************************************

Algorithm Approach:

- Implement the Minimax algorithm in adversarial search to look for future outcomes.
- Due to nature of Minimax algorithm requiring large compute power, Depth-limit is 
the solution for preventing disqualification from testing.
- As the Minimax algorithm, when losing or winning only returns the same value, utilize
the calculation of Sqaure taken as the complement value with winning/losing value to 
prioritize best bite in the best case and best in the worst case.

- Take advantage of a few bar patterns that are obvious by hard-coding certain moves.
to give the opponent a losing pattern to play with.
- Developing a value book; implementing the Minimax algorithm outside of agent code to 
weigh the first bite moves for each bar size.
- Bar patterns that are obvious are being detected in the first column and second column
as well as first row, second row, such as:
	--> 2nd column shorter than 1st column by 1 or vice versa -versa with row
	--> 1st column and 1st row have equal length
	--> When there are only 2 columns or 2 rows left, give the opposite a step pattern.
- Rechecking function to check on minimax returning bite, whether move is a set-up
for losing pattern.

*********************************************************************************

Implementation Analysis:

The agent code works well with the hard-coded moves sections, such as the winning case.
as well as the pattern detections, preventing solely relying on the Minimax algorithm due
to slow performance as well as the unpracticality of the evaluation function in Minimax.

The implementation approach is still improperly functioning, such as in some patterns, 
Unwise moves are still being made, mainly due to an overlap condition or an unwanted 
condition.
*********************************************************************************

Improvment Plan:

- Current algorithm, using the Minimax algorithm, still has limited performance due to slow
compute power. For the next iteration, Alpha-beta Prunning might be the option.
- Upgrade evaluation function to detect and give value to certain bar patterns without
go through the depth of the tree for the winning or losing condition for the return value.
- Expand the detection of bar patterns from 2 rows and 2 columns to 3x3 or even 4x4 for
more hard-coded move.
- Utilize the value lookbook developed outside to hard-code play for each bar size.
- Regoriously testing for consistency performance or detection of error plays by algorithm.
- Improving the rechecking bestBite after using minimax algorithm, whether the bestBite
from minimax algorithm setting for losing patterns.
*********************************************************************************

Upgrade for Iteration 2:

- Adding pattern detection in MiniMax Algorithm to detect any winning/lossing patterns.
Improving the speed as well as increasing depth limit.
- Take advantage of better depth search, gentle bit on some bars, maximizing advantage play.
- Correct the error Plays from pervious Iteration as well as during testing for Iteration 2.

Weakness for this version:

If all possible outcomes lead to lose, bite the poison --> technically should nibble for 
mistake play by opponenet.
*********************************************************************************
*/