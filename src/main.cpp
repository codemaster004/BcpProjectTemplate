#include "cmath"
#include "cstdio"
#include "cstring"

#include "../sdl/include/SDL.h"
#include "../sdl/include/SDL_main.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// FUNCTION HEADERS IGNORE TILL PART 3 //

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
// "sprite" meaning an asset/image or a part of it
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

// draw vertical or horizontal line
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

// END IGNORE TILL PART 3 //

int main() {
	// PART 1. THIS ONLY INITIALIZES THE LIBRARY //

	// Check if the library is able to be imported and start
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// can return an error if for example you have no display in your machine
		printf("SDL_Init error: %s\n", SDL_GetError()); // show what happened
		return 1;
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	// Create a window "application window" with specified size
	// Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff
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

	// This sets current color for drawing
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // you can safely remove for now

	// Setting the title for the provided `window`
	SDL_SetWindowTitle(window, "Hello there. General Kenobi!");

	// You can think of the Surface as a rectangle you are drawing (changing pixels) on
	SDL_Surface *screen; // this time we create variable for our "main" drawing rectangle

	// Create the drawing surface the same size as the main window with standard RGBA color schema
	// "standard RGBA color schema" - red is red and so on,
	// We could change this to interpret (Red, Green, Blue) as (Blue, Green, Red)
	screen = SDL_CreateRGBSurface(
		0, // This should always be 0, however does nothing
		SCREEN_WIDTH, SCREEN_HEIGHT, // the size you want the Surface to be
		32, // Number of bits to use during reading color
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
	); // magical byte numbers interpreting color
	/* Magic bytes?
	 * 0x00 - this a general notation of one Byte. Its value is 0.
	 * 0x01 - this is value 1 (00000001).
	 * 0x0A - this is value 10 (00001010). Bytes use Hex notation
	 * 0xFF - this is value 255 (11111111).
	 * if something has two Bytes 0x01 and 0xFF, we can also write it as 0x01FF
	 *
	 * now imagine a color (purple) represented by only a single big number
	 * 0x00AA00FF (html: #AA00FF)
	 *
	 *     Red        Green       Blue      Opacity
	 * 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
	 * this basically says:
	 * Red value = 0x00AA00FF & 0x00FF0000 = 0x00AA0000
	 * */

	SDL_Texture *texture; // same as "surface" but on GPU
	// Creates basic texture for our whole render
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	// Basically does not matter only as a (part in between) "surface" and "renderer"

	// Hide mouse cursor when over the game window
	SDL_ShowCursor(SDL_DISABLE); // personally I would comment this out as it is annoying

	// PART 2. LOADING THINGIES AND HOPEFULLY SEE SOMETHING //

	SDL_Surface *charset; // Remember this? A drawable rectangle, this time will contain some characters

	// Load bitmap cs8x8.bmp
	// Automatically resize the rectangle to the same size as provided bitmap
	// And draw on it the content of the file
	// basically to store the image inside our game
	charset = SDL_LoadBMP("../static/cs8x8.bmp");
	// Heads up. This will not draw the image on the "window"
	// The only way to show something on out window is to use the `renderer`

	if (charset == nullptr) { // if for any reason we couldn't load the image, for example wrong path
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError()); // show us what the error was
		// Destroy everything (free up memory #benice)
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit(); // Quit the library
		return 1;
	}
	// treat every pixel with given color as transparent
	SDL_SetColorKey(charset, true, 0x000000);

	// Wait a minute! I saw a similar code somewhere...
	SDL_Surface *eti;
	eti = SDL_LoadBMP("../static/eti.bmp");
	if (eti == nullptr) { // repeatable code warning!
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	} // probably should be a function. Don't you think?


	// this is here to reserve a space for a long text
	char text[128];

	// conio had pre-defined colors like #define LIGHT_BLUE 9
	// now we need to create our own colors, with our names to use later
	// `Uint32` is a custom type from SDL it is the same thing as `unsigned int`
	Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	Uint32 green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	Uint32 red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	Uint32 blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	// Again magic byte numbers for rgb color values
	// you can simply read this as html/css colors #FF0000 (red)...

	// SDL_GetTicks() - returns the amount of milliseconds since the library initialization
	Uint32 startTick = SDL_GetTicks(), endTick;
	double delta;

	Uint32 frames = 0; // count of frames in between each check
	double fpsTimer = 0; // +- how much time has passed between showing last frame count
	double fps = 0; // recalculated value of Frames Per Second

	double worldTime = 0; // how much time has passed since the start of the game

	double distance = 0; // reserve a variable for storing the distance that was covered
	double etiSpeed = 1; // speed multiplier for the future

	SDL_Event event;

	bool quit = false;
	while (!quit) {
		// consider a new "game tick" just started and get the time passed
		endTick = SDL_GetTicks();

		// here endTick-startTick is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (endTick - startTick) * 0.001;
		startTick = endTick;

		// Add the time change to the overall time passed
		worldTime += delta;

		// calculate the distance covered. (s = v * t)
		// v - speed of the object, declared above
		// t - time passed since it was last drawn (previous tick)
		distance += etiSpeed * delta;

		// Add value to the timer counting how much time passed between last fps show
		fpsTimer += delta;
		// if fps was last shown more than half a second ago, we can show it one more time
#define FPS_REFRESH_TIME 0.5 // math talk, we show fps ever half a second, hover fps should show frames in a full second
#define FPS_ADJUSTED_TIME (1 / FPS_REFRESH_TIME) // to do this we need to reverse this 1/0.5=2, so we will show real count
		if (fpsTimer > FPS_REFRESH_TIME) {
			// how many frames were in half a second
			fps = frames * FPS_ADJUSTED_TIME; // adjusted to show how much would be in a full second
			frames = 0; // reset fps count
			fpsTimer -= FPS_REFRESH_TIME; // subtract not 0, to preserver small value changes like 0.5003
		}

		// PART 3. DRAWING SOME STUFF //

		// fast way to cover the entire surface with one color
		SDL_FillRect(screen, nullptr, black); // this time we paint entire "screen" black
		// this is done in order to hide what was drawn in previous tick

		// Remember the functions at the top? Go read what they do, and maybe see the actual code at the bottom

		// draw on screen surface our ETI surface
		DrawSurface(screen, eti,
					SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, // math staff for drawing on an arc of the circle
					SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // same thing here, the other cord

		// This top rectangle with information, at least a background for it
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, red, blue);

		// "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		// print for the console and change value of text variable
		snprintf(text, 128, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);

		// see that string above? Yes, show this one. Centered on the screen
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

		//	      "Esc - exit, \030 - faster, \031 - slower"
		snprintf(text, 128, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie"); // also changes text value
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset); // again show, centered

		// last big complicated thing, I promise
		/*
		 * Remember those Surfaces? physically they are just a table of pixels kept in RAM you are replacing
		 * Now, Texture are the same thing but in vRAM, memory in the graphics card.
		 * Renderer is interpreting/rendering the Texture table and showing this on actual computer screen
		 * Wasn't that had eh?
		 */

		// This part is required for anything to show stuff.
		// copy screen Surface to screen Texture
		SDL_UpdateTexture(texture, nullptr, screen->pixels, screen->pitch);

		// clearing the renderer
		SDL_RenderClear(renderer); // can be commented, maybe should

		// copy entire screen Texture to the screen Renderer
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);

		// this is the actual part that shows our created everything
		SDL_RenderPresent(renderer);

		// fake while loop, only here to handle multiple key preses at once
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN: // event of pressing down a key on keyboard
					// what should we do?
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = true; // Esc = Quit
					else if (event.key.keysym.sym == SDLK_UP) etiSpeed = 2.0; // Arrow Up Fly faster by changing speed
					else if (event.key.keysym.sym == SDLK_DOWN) etiSpeed = 0.3; // Reduce the speed
					break;
				case SDL_KEYUP: // similarly event when you stop pressing
					etiSpeed = 1.0; // reset the speed of ETI
					break;
				case SDL_QUIT: // important duck. This is for closing the window by the regular "X" button. DON'T FORGET
					quit = true;
					break;
			}
		}

		frames++; // one more frame was generated
	}

	return 0; // READING DONE!!!
}

void DrawString(SDL_Surface *screen, int x, int y, const char *text,
				SDL_Surface *charset) {
	int offX, offY;
	int character;

	// SDL_Rect - structure keeping information about origin (x, y) (top left corner) and its (w, h) (width and height)
	SDL_Rect src, dest;

	// basic assignment to a struct
	src.w = 8;
	src.h = 8;
	dest.w = 8;
	dest.h = 8;

	// while we are not at the end of the string '/0' do this...
	while (*text) {
		character = *text & 255; // convert 'char' to number with a "mask"
		// now knowing the characters are position in rows of 16 elements
		// from numerical value we calculate its offset from top and left
		offY = (character / 16) * 8;
		offX = (character % 16) * 8;

		src.x = offX;
		src.y = offY;
		dest.x = x;
		dest.y = y;

		// Draw the letter
		SDL_BlitSurface(charset, &src, screen, &dest);
		/* This function takes in 4 argument, or more precisely two groups of arguments
		 * each group consists of 2 args.
		 *
		 * group looks like this: (surface with some drawings, information [x, y, w, h] what part interest us)
		 * now the full function arguments can be read: (copy from, copy to)
		 */

		// Move x by width of the letter and increase the letter
		x += 8;
		text++;
	}
}

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) { // remember (x, y) cords of the center
	// SDL_Rect - structure keeping information about origin (x, y) (top left corner) and its (w, h) (width and height)
	SDL_Rect dest;

	// Determine the top left corner
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	// copy width and height
	dest.w = sprite->w;
	dest.h = sprite->h;
	// draw entire sprite on screen at given position
	SDL_BlitSurface(sprite, nullptr, screen, &dest);
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) { // Warning! Wibbly wobbly, timey wimey stuff
	// how about we move on and just take for granted that this works? Okay? Great!

	int bpp = surface->format->BytesPerPixel; // one pixel consists of N Bytes, wee need to know of how many
	// surface->pixels is type of `void *` void pointers, whenever we do something directly with it,
	// we need to reinterpret it to use operate on Bytes
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
	/*
	 * Seriously why you are reading this, go touch some gras.
	 * Uint8 *p = (Uint8 *) - this is the type we are operating on, a "SiMpLiFiCaTiOn" for pointer arithmetics
	 * surface->pixels - pointer to array of pixels, yes 1D array #libraryOptimization
	 * ... now will come pointer arithmetics for determining the correct spot to alter values to change the color of pixel
	 * + y * surface->pitch - `pitch` holds info about how long in Bytes one row is, that is how we get correct row
	 * + x * bpp - Byte size of one Pixel times which pixel from left it is
	 * now we should have a pointer to the beginning of a pixel value.
	 */
	// first reinterpret the pointer to be the size of out format
	*(Uint32 *) p = color; // alter the value
	// congrats, you changed one pixel
	// almost no students were harmed in writing this explanation
}

void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	// yes! you guessed correctly.
	for (int i = 0; i < l; i++) { // this iterates over the line and draws every pixel, separately
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	// Drawing borderlines separately, so we can have outlines in a different color
	DrawLine(screen, x, y, k, 0, 1, outlineColor);             // left
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);     // right
	DrawLine(screen, x, y, l, 1, 0, outlineColor);             // top
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);     // bottom

	for (int i = y + 1; i < y + k - 1; i++) // iterate over y value and fill the remaining space
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
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