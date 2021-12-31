#include "Game.hpp"
#include "SDL_events.h"

Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN || SDL_WINDOW_OPENGL;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    cout << "Initialized!" << endl;
    window = SDL_CreateWindow("EPS", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height, flags);

    if (!window) {
      printf("Could not create window: %s\n", SDL_GetError());
      isRunning = false;
      return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
      printf("Could not create renderer: %s\n", SDL_GetError());
      isRunning = false;
      return;
    }

    backgroundImage = IMG_Load("assets/background.png");
    background = SDL_CreateTextureFromSurface(renderer, backgroundImage);

    isRunning = true;
  } else {
    isRunning = false;
  }
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update() {}

void Game::render() {
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, background, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_FreeSurface(backgroundImage);
  SDL_DestroyTexture(background);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

bool Game::running() { return isRunning; }
