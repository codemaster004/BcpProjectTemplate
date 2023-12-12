
#include "cstdio"

#include "../sdl/include/SDL.h"

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

int main() {
	// PART 1. THIS ONLY INITIALIZES THE LIBRARY

	// Check if the library is able to be imported and start
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// can return an error if for example a pat is missing
		printf("SDL_Init error: %s\n", SDL_GetError()); // show what happened
		return 1;
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	// Create a window "application window" with specified size (use (0, 0) for full screen)
	// Also create render for this window, reader meaning this space under the "window bar"
	int initError = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	// returns a value 0 if was able to create window
	if (initError != 0) {
		// if it didn't manage to create window quit everything
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError()); // show what happened
		return 1;
	}

	// SDL_SetHint - sets a value to given setting in SDL
	// SDL_HINT_RENDER_SCALE_QUALITY - setting name meaning how images are scaled
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // you can safely remove for now

	// Tell the render what is the area he will be drawing/rendering
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT); // for safety leave this "here"

	// This sets default drawing color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Setting the title for the provided `window`
	SDL_SetWindowTitle(window, "Hello there. General Kenobi!");

	// You can think of the Surface as a rectangle you are drawing (changing pixels) on
	SDL_Surface *screen; // this time we create variable for out "main" drawing rectangle

	// Create the drawing surface the same size as the main window with standard RGBA color schema
	// "standard RGBA color schema" - red is red and so on,
	// We could change this to interpret (Red, Green, Blue) as (Blue, Green, Red)
	screen = SDL_CreateRGBSurface(
		0, // This should always be 0, however does nothing
		SCREEN_WIDTH, SCREEN_HEIGHT, // the size you want the Surface to be
		32, // Size in bits of the next 4 variables to come
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
	); // magical byte numbers interpreting color
	/* Magic bytes?
	 * 0x00 - this a general notation of one Byte. Its value is 0.
	 * 0x01 - this is value 1 (00000001).
	 * 0x0A - this is value 10 (00001010). Bytes use Hex notation
	 * 0xFF - this is value 255 (11111111).
	 * if something has two Bytes we 0x01 and 0x0F, we can also write it as 0x01FF
	 *
	 * now imagine a color (purple) represented by only a single big number
	 * 0x00AA00FF (html: #AA00FF)
	 *
	 *     Red        Green       Blue      Opacity
	 * 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
	 * this basically says:
	 * Red value = 0x00AA00FF & 0x00FF0000 = 0x00AA0000
	 * */

	SDL_Texture *texture;
	// Creates basic texture for our hole render
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
							   SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH, SCREEN_HEIGHT);
	// Probably does not matter ignore for now

	// Hide mouse cursor when over the game window
	SDL_ShowCursor(SDL_DISABLE); // personally I would comment this out as it is annoying

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