#include<stdio.h>
#include<SDL/SDL.h>

typedef struct
{
   int x,y;
   short life;
   char *name;
} Man;

int processEvents(SDL_Window *window, Man *m) {
    SDL_Event event;
    int done = 0;

    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
            if(window) {
                SDL_DestroyWindow(window);
                window = NULL;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done=1;
                break;
            case SDLK_LEFT:
                m->x -= 10;
                break;
            case SDLK_RIGHT:
                m->x += 10;
                break;
            case SDLK_DOWN:
                m->y += 10;
                break;
            case SDLK_UP:
                m->y -= 10;
                break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            done=1;
            break;
        default:
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    return done;
}

void doRender(SDL_Renderer *renderer, Man *m) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = { m->x, m->y, 200, 200 };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

}

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Man m;
    m.x = 220;
    m.y = 140;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Game Programming",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                640,
                                480,
                                0
                                );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //The window is open: enter the event loop
    int done = 0;
    

    while (!done) {
        //Checks for events
        done = processEvents(window, &m);

        doRender(renderer, &m);

        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(window);
    SDL_Quit();
}