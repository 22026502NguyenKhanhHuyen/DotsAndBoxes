#include "picksize.h"
#include "init.h"

MenuSize::MenuSize()
{
    exit = false;
    out = false;
};

void MenuSize::initTex( SDL_Renderer* gRenderer )
{
    TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 40 );
    SDL_Color gColor = { 70, 70, 70 };

    Tex = loadFromRenderedText( gRenderer, "Please choose board size!", gFont, gColor );
    Tex1 = loadFromRenderedText( gRenderer, "3x3", gFont, gColor );
    Tex2 = loadFromRenderedText( gRenderer, "5x5", gFont, gColor );
    Tex3 = loadFromRenderedText( gRenderer, "7x7", gFont, gColor );
    Tex4 = loadFromRenderedText( gRenderer, "9x9", gFont, gColor );
}

SDL_Rect rect1 = { 205, 165, 90, 60 };
SDL_Rect rect2 = { 205, 305, 90, 60 };
SDL_Rect rect3 = { 445, 165, 90, 60 };
SDL_Rect rect4 = { 445, 305, 90, 60 };

void MenuSize::renderTex( SDL_Renderer* gRenderer )
{
//    //Vẽ ô vuông trong Menu
//    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );

//    SDL_Rect MENU1 = { 180, 140, 140, 100 };
//    SDL_RenderDrawRect( gRenderer, &MENU1);
//
//    SDL_Rect MENU2 = { 180, 280, 140, 100 };
//    SDL_RenderDrawRect( gRenderer, &MENU2 );
//
//    SDL_Rect MENU3 = { 420, 140, 140, 100 };
//    SDL_RenderDrawRect( gRenderer, &MENU3 );
//
//    SDL_Rect MENU4 = { 420, 280, 140, 100 };
//    SDL_RenderDrawRect( gRenderer, &MENU4 );


    SDL_Rect rectMENU = { 120, 40, 500, 70 };
    SDL_RenderCopy( gRenderer, Tex, NULL, &rectMENU );

    SDL_RenderCopy( gRenderer, Tex1, NULL, &rect1 );

    SDL_RenderCopy( gRenderer, Tex2, NULL, &rect2 );

    SDL_RenderCopy( gRenderer, Tex3, NULL, &rect3 );

    SDL_RenderCopy( gRenderer, Tex4, NULL, &rect4 );
}

Tus MenuSize::handleEvent( SDL_Renderer* gRenderer, SDL_Event e, SDL_Rect R )
{
    Tus currentEvent = DEFAULT;
    //If mouse event happened
        if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

            //Check if mouse is in button
            bool inside = true;

            //Mouse is left of the button
            if( y < R.y )
            {
                inside = false;
            }
            //Mouse is right of the button
            else if( y > R.y+R.h )
            {
                inside = false;
            }
            //Mouse above the button
            else if( x < R.x )
            {
                inside = false;
            }
            //Mouse below the button
            else if( x > R.x+R.w )
            {
                inside = false;
            }

            //Mouse is outside button
            if( !inside )
            {
                if(currentEvent == MOUSE)
                {
                    currentEvent = DEFAULT;
                }
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                if( currentEvent == DEFAULT || currentEvent == MOUSE )
                    switch( e.type )
                    {
                        case SDL_MOUSEMOTION:
                        {
                            currentEvent = MOUSE;
                            break;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        {
                            currentEvent = CLICK;
                            break;
                        }
                    }
            }
        }
    return currentEvent;
}

void MenuSize::CheckEvent( SDL_Renderer* gRenderer, SDL_Event e )
{
    Tus T1, T2, T3, T4;

    TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 40 );
    SDL_Color gColor1 = { 100, 100, 0 };
    SDL_Color gColor2 = { 100, 0, 0 };

    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT )
        {
            exit = true;
            out = true;
        }

        T1 = handleEvent( gRenderer, e, rect1 );
        T2 = handleEvent( gRenderer, e, rect2 );
        T3 = handleEvent( gRenderer, e, rect3 );
        T4 = handleEvent( gRenderer, e, rect4 );
    }

    if( T1 == DEFAULT )
    {
        SDL_DestroyTexture( Tex1 );
        Tex1 = loadFromRenderedText( gRenderer, "3x3", gFont, gColor1 );
    }
        if( T2 == DEFAULT )
    {
        SDL_DestroyTexture( Tex2 );
        Tex2 = loadFromRenderedText( gRenderer, "5x5", gFont, gColor1 );
    }
        if( T3 == DEFAULT )
    {
        SDL_DestroyTexture( Tex3 );
        Tex3 = loadFromRenderedText( gRenderer, "7x7", gFont, gColor1 );
    }
        if( T4 == DEFAULT )
    {
        SDL_DestroyTexture( Tex4 );
        Tex4 = loadFromRenderedText( gRenderer, "9x9", gFont, gColor1 );
    }

    if( T1 == MOUSE )
    {
        SDL_DestroyTexture( Tex1 );
        Tex1 = loadFromRenderedText( gRenderer, "3x3", gFont, gColor2 );
    }
    if( T2 == MOUSE )
    {
        SDL_DestroyTexture( Tex2 );
        Tex2 = loadFromRenderedText( gRenderer, "5x5", gFont, gColor2 );
    }
    if( T3 == MOUSE )
    {
        SDL_DestroyTexture( Tex3 );
        Tex3 = loadFromRenderedText( gRenderer, "7x7", gFont, gColor2 );
    }
    if( T4 == MOUSE )
    {
        SDL_DestroyTexture( Tex4 );
        Tex4 = loadFromRenderedText( gRenderer, "9x9", gFont, gColor2 );
    }


    if( T1 == CLICK )
    {
        Change = 3;
        exit = true;
    }
    else
        if( T2 == CLICK )
    {
        Change = 2;
        exit = true;
    }
    else
        if( T3 == CLICK )
    {
        Change = 1;
        exit = true;
    }
    else
        if( T4 == CLICK )
    {
        Change = 0;
        exit = true;
    }
}

bool MenuSize::CheckExit()
{
    return (exit||out);
}

void MenuSize::reset()
{
    exit = false;
    Change = 0;
}
