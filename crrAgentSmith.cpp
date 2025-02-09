// YOUR NAME: ___
//
// CS 4318, spring 2024
// Agent Challenge 5: Chocolate Russian roulette
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this crrAgentSmith.cpp file to crrAgentJones.cpp and the
// crrAgentSmith function below to crrAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for yours to play against,
// but turn in only one.  Test your agent(s) with
//
//    nice bash crrBuild.bash
//
// and then
//
//    nice ./crrRunSim
//
// Each submitted agent will play each other using chocolate bar sizes
// varying from 3x4 to 6x9, once moving first and once moving second, to
// determine the standings, which will be posted soon after the agents are
// due.

#include "crr.h"

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
}

// Rename and complete this agent function.
ChocolateSquareLocation crrAgentSmith(const ChocolateBar &bar)
{
   // Your function must end up returning a valid ChocolateSquareLocation.
   // No random-number generation allowed!

   // Replace this return statement with your agent code.
   // (The (0, 0) bite is not a good one, but it's guaranteed to be legal.)
   return ChocolateSquareLocation(0, 0);
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.

*/
