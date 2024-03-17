#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

#include <SDL.h>

#define ERROR_EXIT(...) do{ fprintf(stderr, "%s:%d", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__);  exit(1); }while(0)
#define ERROR_RETURN(R,...) do{ fprintf(stderr, "%s:%d", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__);  return R; }while(0)

typedef struct context {
  bool is_running;
  SDL_Event sdl_event;
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
} Context;

void setup(Context *context);
void run(Context *context);
void cleanup(Context *context);

int main(int argc, char *argv[])
{
  Context context;
  setup(&context);
  run(&context);
  cleanup(&context);
  return 0;
}

void setup(Context *context)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    ERROR_EXIT("Unable to initialize SDL: %s\n", SDL_GetError());
  }

  context->sdl_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

  if (!context->sdl_window)
  {
    ERROR_EXIT("Unable to create window: %s\n", SDL_GetError());
  }

  context->sdl_renderer = SDL_CreateRenderer(context->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!context->sdl_renderer)
  {
    ERROR_EXIT("Unable to create renderer: %s\n", SDL_GetError());
  }

  context->is_running = true;
}

void run(Context *context)
{
  while (context->is_running)
  {
    while (SDL_PollEvent(&context->sdl_event))
    {
      if (context->sdl_event.type == SDL_QUIT || context->sdl_event.type == SDL_KEYDOWN)
      {
        context->is_running = false;
      }
    }
    SDL_SetRenderDrawColor(context->sdl_renderer, 0x30, 0x60, 0x90, 0xFF);
    SDL_RenderClear(context->sdl_renderer);
    SDL_RenderPresent(context->sdl_renderer);
  }
}

void cleanup(Context *context)
{
  if (context->sdl_renderer)
  {
    SDL_DestroyRenderer(context->sdl_renderer);
  }

  if (context->sdl_window)
  {
    SDL_DestroyWindow(context->sdl_window);
  }

  SDL_Quit();
}

