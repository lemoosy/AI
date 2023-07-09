#include "Input.h"

void Input_Update(Input* input)
{
    SDL_Event events = { 0 };

    input->left = false;
    input->right = false;
    input->up = false;
    input->down = false;

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_KEYDOWN:

            switch (events.key.keysym.scancode)
            {
            case SDL_SCANCODE_LEFT:
                input->left = true;
                break;

            case SDL_SCANCODE_RIGHT:
                input->right = true;
                break;

            case SDL_SCANCODE_UP:
                input->up = true;
                break;

            case SDL_SCANCODE_DOWN:
                input->down = true;
                break;

            case SDL_SCANCODE_F1:
                input->f1 = !input->f1;
                break;

            case SDL_SCANCODE_F2:
                input->f2 = !input->f2;
                break;

            case SDL_SCANCODE_F3:
                input->f3 = !input->f3;
                break;

            case SDL_SCANCODE_F4:
                input->f4 = !input->f4;
                break;

            case SDL_SCANCODE_F5:
                input->f5 = !input->f5;
                break;

            case SDL_SCANCODE_ESCAPE:
                input->quit = true;
                break;
            }

            break;

        case SDL_QUIT:

            input->quit = true;

            break;
        }
    }
}
