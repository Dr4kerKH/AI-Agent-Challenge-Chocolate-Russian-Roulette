#include "crr.h"
namespace
{
// Function for Calculation of Square taken
int calSquareTaken(const ChocolateBar &bar, const ChocolateBar &newBar, bool isMaxiPlayer) {
	int	before, after, biteColumn, biteRow;
	before = after = 0;
	// If maxi player, return square taken as positive
	if (isMaxiPlayer) {
		for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1){
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
		for (biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1){
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
// MiniMax Algorithm Recurssively till return value
int value(const ChocolateBar &bar, int depth, bool isMaxiPlayer) {
	
	ChocolateBar newBar;
	ChocolateSquareLocation bestBite, bite;
	int bestOutcome, biteColumn, biteRow, outcome;
	
	// Terminate clause, win or lose
	if (!bar.isAnyLeft())
		return isMaxiPlayer? 1000 : -1000;
	// Depth limits to 9
	if (depth > 9)
		return isMaxiPlayer? 10:-10;
	if (isMaxiPlayer? bestOutcome = INT_MIN: bestOutcome = INT_MAX); // Initialized bestOutcome
	
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
	for (int i = bar.getWidth() - 1; i >= 0; i -= 1)
		for (int j = bar.getHeight() - 1; j >= 0; j -= 1)
			if (!bar.isSquareThere(i, j))
				return false;
	return true;
}
// Function get remaining width of passing col
int getRemainingWidth(const ChocolateBar &bar, const int col) {
	int remain = 0;	
	for (int x = bar.getWidth() - 1; x >= 0; x -= 1)
		if (bar.isSquareThere(x, col)) {
			remain = x;
			break;
		}
	return remain;
}
// Function get remaining height of passing row
int getRemainingHeight(const ChocolateBar &bar, const int row) {
	int remain = 0;
	for (int x = bar.getHeight() - 1; x >= 0; x -= 1)
		if (bar.isSquareThere(row, x)) {
			remain = x;
			break;
		}
	return remain;
}
// Function recheck the best bite
bool isBadMove(const ChocolateBar &bar, ChocolateSquareLocation bite, int w0, int w1, int h0, int h1) {
	ChocolateBar newBar;
	newBar = bar;
	newBar.takeBite(bite);
	if (newBar.isSquareThere(2, 0) && h0 - h1 == 1 && h1 > 0)
		return true;
	if (newBar.isSquareThere(0, 2) && w0 - w1 == 1 && w1 > 0)
		return true;
	return false;
}
}

ChocolateSquareLocation crrAgentFox(const ChocolateBar &bar)
{
	int w0, h0, w1, h1;
	int width = bar.getWidth(), height = bar.getHeight();
	bool full = isFull(bar);
	
	// Find remaining bar in column 0,1,2
	w0 = getRemainingWidth(bar, 0);
	w1 = getRemainingWidth(bar, 1);
//	w2 = getRemainingWidth(bar, 2);
	// Find reminaing bar in row 0,1,2
	h0 = getRemainingHeight(bar, 0);
	h1 = getRemainingHeight(bar, 1);
//	h2 = getRemainingHeight(bar, 2);
	
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
	if (w1 > 0 && !(w1 + 2 > w0) && bar.isSquareThere(w1+3, 0))
		return ChocolateSquareLocation(w1 + 3, 0);
	
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
		if (bar.isSquareThere(2, 1) && !isBadMove(bar, ChocolateSquareLocation(2, 1), w0, w1, h0, h1))
			return ChocolateSquareLocation(2, 1);
	}
	if (bar.getWidth() % 2 == 1 && full) {
		if (bar.isSquareThere(1,2) && !isBadMove(bar, ChocolateSquareLocation(1, 2), w0, w1, h0, h1))
			return ChocolateSquareLocation(1, 2);
	}
	/*
	if (!bar.isSquareThere(1, 2) && !bar.isSquareThere(2, 1) && bar.isSquareThere(1, 1) && differenceArms != 0) {
		if (h0 > w0 && !isBadMove(bar, ChocolateSquareLocation(0, w0)))
			return ChocolateSquareLocation(0, w0);
		if (h0 < w0 && !isBadMove(bar, ChocolateSquareLocation(h0, 0)))
			return ChocolateSquareLocation(h0, 0);
	}*/
	
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
	// Check best bite before return
	if (isBadMove(bar, bestBite, w0, w1, h0, h1)) {
		newBar = bar;
		newBar.takeBite(bestBite);
		
		w0 = getRemainingWidth(newBar, 0);
		w1 = getRemainingWidth(newBar, 1);
		h0 = getRemainingHeight(newBar, 0);
		h1 = getRemainingHeight(newBar, 1);
		
		if (h0 - h1 == 1 && newBar.isSquareThere(1, h0-1))
			return ChocolateSquareLocation(1, h0-1);
		if (w0 - w1 == 1 && newBar.isSquareThere(w0-1, 1))
			return ChocolateSquareLocation(w0-1, 1);
	}
	
	return bestBite;
}