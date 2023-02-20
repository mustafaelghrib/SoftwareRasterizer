#include <windows.h>
#include "SDL.h"
#include <stdlib.h>
#include <iostream>
#include "timer.h"

using namespace std;

typedef unsigned long long uint64;

int gScreenWidth = 800;
int gScreenHeight = 600;

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Rect rectangle;

void Create() {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Pixel Screen",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        gScreenWidth,
        gScreenHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void DestroyWindow() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
}

void plot_pixel_ndc(float ndcX, float ndcY, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

    float wdcX = ndcX * (gScreenWidth / 2) + (gScreenWidth / 2);
    float wdcY = ndcY * (gScreenHeight / 2) + (gScreenHeight / 2);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, (int)wdcX, (int)wdcY);
}

void plot_box_ndc(double ndcX, double ndcY, int rWidth, int rHight, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {

    double wdcX = ndcX * (gScreenWidth / 2.0) + (gScreenWidth / 2.0);
    double wdcY = ndcY * (gScreenHeight / 2.0) + (gScreenHeight / 2.0);

    rectangle.x = (int)floor(wdcX);
    rectangle.y = (int)floor(wdcY);
    rectangle.w = rWidth;
    rectangle.h = rHight;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rectangle);
}

int main(int argc, char* argv[]) {

    Timer timer;

    timer.StartTimer();

    Create();

    Uint32 windowID = SDL_GetWindowID(window);

    while (1) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_WINDOWEVENT: {
                if (event.window.windowID == windowID) {
                    switch (event.window.event) {

                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        gScreenWidth = event.window.data1;
                        gScreenHeight = event.window.data2;
                        break;
                    }

                    case SDL_WINDOWEVENT_CLOSE: {
                        event.type = SDL_QUIT;
                        SDL_PushEvent(&event);
                        break;
                    }

                    }
                }
                break;
            }

            case SDL_QUIT: { return 0; }
            }

        }

        plot_box_ndc(0, 0, 50, 50, 255, 0, 0, 0);

        SDL_RenderPresent(renderer);

        timer.QueryCounter();

        uint64 deltaSeconds = timer.DeltaTimeS();

        if (deltaSeconds > 5.0f) {
            cout << "5 seconds elapsed" << endl;
            timer.StartTimer();
        }
    }

    DestroyWindow();

    return 0;
}