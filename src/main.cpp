
#include "../sdl/include/SDL.h"

int main() {
	return 0;
}

/**
 * TODO [x]: Write a TODO list
 * TODO [ ]: Rewrite template file
 *    TODO [ ]: Understand
 *    TODO [ ]: Restructure
 *    TODO [ ]: Add comments
 *    TODO [ ]: Share
 *
 * ! MVP (Minimal Viable Product)
 * TODO [ ]: Basic UI. (Board outline, space for some text, key binds (Esc, N))
 * TODO [ ]: 1 game lvl. (floor, several "platforms", "ladders")
 * TODO [ ]: Moving character (use arrows to move, move vert only on ladders)
 * TODO [ ]: Display the time passed in game
 *
 * TODO [ ]: A. Jumps (1 ptk)
 *    TODO [ ]: After pressing SPACE player moves up, comes back down
 *    TODO [ ]: Player should not jump thought walls / ceilings
 *    TODO [ ]: It should be possible to jump onto next "platform"
 *    TODO [ ]: if(*C) jumping over barrels should be possible
 * TODO [ ]: B. More game Stages (1 ptk)
 *    TODO [ ]: At least 3 different game "stages"
 *    TODO [ ]: User should be able to switch between them using Number Keys (1, 2, 3...)
 *    TODO [ ]: if(*D) "program" should know we changed stage and ?show it on the screen?
 * TODO [ ]: C. Barrels exists and move (1 ptk)
 *    TODO [ ]: Barrels appear at a specific location
 *    TODO [ ]: Movement of the barrel should be "parameterized"
 *    TODO [ ]: The "Program" should detect collision and if(*D) do something...
 * TODO [ ]: D. A LOT (1 ptk)
 * 	  TODO [ ]: Starter Screen menu (Exit, Save, Read, Check results, Select a stage)
 * 	  TODO [ ]: Entering player names (vis text, ability to delete)
 * 	  TODO [ ]: Display number of lives
 * 	  TODO [ ]: Die if touch a barrel
 * 	  TODO [ ]: if(*F) Die show some points
 * 	  TODO [ ]: Out of lives show main menu and if(*H) save score
 * 	  TODO [ ]: Get to top next stage
 * TODO [ ]: E. Animations (2 ptk)
 *    TODO [ ]: Animation for climbing
 *    TODO [ ]: Jumping
 *    TODO [ ]: if(*C) Barrels rolling
 * TODO [ ]: F. Counting (1 ptk)
 *    TODO [ ]: Keep count of number of "Points"
 *    TODO [ ]: Keep "points" between "stages"
 *    TODO [ ]: if(*C) extra "points" for jumping over barrels
 *    TODO [ ]: Picking up "trophy"
 * TODO [ ]: G. Saving best score (1 ptk)
 *    TODO [ ]: Game finishes (is won)
 *    TODO [ ]: Save result with Entered Nick to file
 *    TODO [ ]: Display results on the screen (only top 10)
 *    TODO [ ]: "Scrollable" result list
 *    TODO [ ]: *!F show time not score
 * TODO [ ]: H. Advance Looks (1 ptk)
 *    TODO [ ]: The Platforms are tilted
 * TODO [ ]: I. Encoding "stage" in a file (1 ptk)
 *    TODO [ ]: Create a file with your own encoding of a stage (easily editable)
 *    TODO [ ]: Read the "Stage File" upon starting the "stage"
 *    TODO [ ]: Amount of object in the file should not be limited
 */

/*
 * ? Point 4. "The time should be displayed along with the information about implemented requirements."
 *  	- does this mean "somewhere on the screen we are supposed to display letters (A, H, D) with implemented points?
 * ? "Character movement and control parameters should be easy to change to achieve smooth control." wtf?
 *  	- what does the "to achieve smooth control." mean?
 * ? Menu: Read
 * ? Menu: Check results
 * ? Menu: Save, save what?
 * ? Is there any particular order we are supposed to complete those requirements?
 * ? Point B.c. "signal this event (continued in point D)"
 * 		- never continued, what does it mean, what should the event display/ change?
 * ?
 */