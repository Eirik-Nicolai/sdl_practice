#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string_view>
/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int main(int, char**){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "HELLO WORLD" << std::endl;
    SDL_WindowFlags flags;
    flags = SDL_WINDOW_RESIZABLE;
    SDL_Window *window = SDL_CreateWindow("Window", 400, 400, flags);
    if(!window)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, "");
    if(!renderer)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_CreateSurface(100, 100, SDL_PIXELFORMAT_ARGB128_FLOAT);

    if(!surface)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    TTF_Init();

    auto font = TTF_OpenFont("FiraCodeNerdFontMono-Bold.ttf", 30.0);
    if(!font)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;

        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Color white{255,255,255};
    const std::string_view text = "Hello world !";
    surface = TTF_RenderText_Blended(font, text.data(), text.length()*2, white);

    if(!surface)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;

        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(!texture)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;

        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    SDL_FRect textRect;
    textRect.w = surface->w;
    textRect.h = surface->h;
    textRect.x = 10;
    textRect.y = 10;

    SDL_DestroySurface(surface);

    while(1)
    {
        SDL_Event e;

        SDL_WaitEvent(&e);

        if(e.type == SDL_EVENT_QUIT)
        {
            break;
        }
        else if (e.type == SDL_EVENT_KEY_DOWN)
        {
            if(e.key.key == SDLK_LEFT)
            {
                textRect.x -= 1;
            }
        }



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, texture, nullptr, &textRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
