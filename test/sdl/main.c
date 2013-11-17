# include <SDL2/SDL.h>   /* All SDL App's need this */
# include <SDL2/SDL_events.h>   /* All SDL App's need this */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 400
# define HEIGHT 400

# include "getput.c"

int main(int argc, char* argv[]) {
  unsigned int running = 8;

  SDL_Window *window;                    // Declare a pointer
  SDL_Event event; /* Event structure */
  SDL_Surface *surface; /* the surface*/


  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
      "Navier & Stokes",                  // window title
      SDL_WINDOWPOS_UNDEFINED,           // initial x position
      SDL_WINDOWPOS_UNDEFINED,           // initial y position
      WIDTH,                               // width, in pixels
      HEIGHT,                               // height, in pixels
      SDL_WINDOW_OPENGL                  // flags - see below
      );

  // Check that the window was successfully made
  if (window == NULL) {
    // In the event that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }
  // The window is open: enter program loop (see SDL_PollEvent)
  
  surface = SDL_GetWindowSurface(window);
  SDL_FillRect(surface , NULL , 0x441133);
  SDL_UpdateWindowSurface(window);
  srand(45);

  while (running)
  {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_MOUSEMOTION:
          putpixel(surface,event.motion.x, event.motion.y,rand());
          SDL_UpdateWindowSurface(window);
          break;
        case SDL_SYSWMEVENT:
          printf("SysWMEvent\n");
          break;
        case SDL_KEYDOWN:
          printf("SDL_KEYDOWN\n");
          break;
        case SDL_KEYUP:
          printf("SDL_KEYUP\n");
          break;
        case SDL_MOUSEBUTTONUP:
          printf("SDL_MOUSEBUTTONUP\n");
          break;
        case SDL_MOUSEBUTTONDOWN:
          printf("SDL_MOUSEBUTTONDOWN\n");
          break;
        case SDL_JOYAXISMOTION:
          printf("SDL_JOYAXISMOTION\n");
          break;
        case SDL_JOYBALLMOTION:
          printf("SDL_JOYBALLMOTION\n");
          break;
        case SDL_JOYHATMOTION:
          printf("SDL_JOYHATMOTION\n");
          break;
        case SDL_JOYBUTTONUP:
          printf("SDL_JOYBUTTONUP\n");
          break;
        case SDL_JOYBUTTONDOWN:
          printf("SDL_JOYBUTTONDOWN\n");
          break;
        case SDL_QUIT:
          printf("SDL_QUIT\n");
          running = 0;
          break;
        case SDL_USEREVENT:
          printf("SDL_USEREVENT\n");
          break;
        case 512:
          break;
        default:
          printf("Unhandled Event %d ! %d\n",running--,event.type);
          break;
      }
    }
  }

  SDL_FreeSurface(surface);

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();
  return 0;
}

