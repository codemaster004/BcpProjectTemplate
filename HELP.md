
# What does this Mean?!?

## Graphical keywords

---

`Surface` - An area on a plane that I __suppose__ I have access to and am __supposed to__ do *something* with.

`SDL_Window` - struct that holds all info about the Window itself: size, position, full screen, borders ...

`SDL_Renderer` - 

# SDL Graphics Rendering

## Setting the Draw Color
To set the draw color for the rendering context, use:
```c
SDL_SetRenderDrawColor(renderer, r, g, b, a);
```

This function sets the color you will use to clear the screen with `SDL_RenderClear()`.

## Clearing the Render Target

`SDL_Renderer` is a struct that handles all rendering.
It is tied to a `SDL_Window` so it can only render within that `SDL_Window`.
It also keeps track the settings related to the rendering.
There are several important functions tied to the `SDL_Renderer`

- `SDL_SetRenderDrawColor(renderer, r, g, b, a);`
  - This sets the color you clear the screen to ( see below )
- `SDL_RenderClear(renderer);`
  - This clears the rendering target with the draw color set above
- `SDL_RenderCopy(`
  - This is probably the function you'll be using the most, it's used for rendering a `SDL_Texture` and has the following parameters

SDL_Renderer*   renderer,
The renderer you want to use for rendering.
SDL_Texture*    texture,
The texture you want to render.
const SDL_Rect* srcrect, The part of the texture you want to render, NULL if you want to render the entire texture
const SDL_Rect* dstrect)
Where you want to render the texture in the window. If the width and height of this SDL_Rect is smaller or larger than the dimensions of the texture itself, the texture will be stretched according to this SDL_Rect
SDL_RenderPresent(renderer);
The other SDL_Render* functions draws to a hidden target. This function will take all of that and draw it in the window tied to the renderer.

