#include "menu.h"
#include "init.h"

menu::menu()
{
    exit = false;
    out = false;
};

void menu::initTex( SDL_Renderer* gRenderer )
{
    TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 80 );
    SDL_Color gColor = { 211, 186, 135 };

    Tex = loadFromRenderedText( gRenderer, "Dots Boxes", gFont, gColor );
    Tex1 = loadFromRenderedText( gRenderer, "Play Game", gFont, gColor );
    Tex2 = loadFromRenderedText( gRenderer, "Exit Game", gFont, gColor );
}

SDL_Rect rec1 = { 300, 170, 170, 70 };
SDL_Rect rec2 = { 300, 260, 160, 60 };

void menu::renderTex( SDL_Renderer* gRenderer )
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


    SDL_Rect rectMENU = { 260, 70, 240, 70 };
    SDL_RenderCopy( gRenderer, Tex, NULL, &rectMENU );

    SDL_RenderCopy( gRenderer, Tex1, NULL, &rec1 );

    SDL_RenderCopy( gRenderer, Tex2, NULL, &rec2 );
}

MenuStatus menu::handleEvent( SDL_Renderer* gRenderer, SDL_Event e, SDL_Rect R )
{
    MenuStatus currentEvent = DEFAUL;
    //If mouse event happened
       // if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN )
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
                if(currentEvent == MOUS)
                {
                    currentEvent = DEFAUL;
                }
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                currentEvent = MOUS;
                if( currentEvent == DEFAUL || currentEvent == MOUS )
                    switch( e.type )
                    {
                        case SDL_MOUSEMOTION:
                        {
                            currentEvent = MOUS;
                            break;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        {
                            currentEvent = CLIC;
                            break;
                        }
                    }
            }
        }
    return currentEvent;
}

void menu::CheckEvent( SDL_Renderer* gRenderer, SDL_Event e )
{
    MenuStatus T1, T2;

    TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 40 );
    SDL_Color gColor1 = { 133, 171, 213 };
    SDL_Color gColor2 = { 128, 110, 236 };

    //while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT )
        {
            exit = true;
            out = true;
        }

        T1 = handleEvent( gRenderer, e, rec1 );
        T2 = handleEvent( gRenderer, e, rec2 );
    }

    if( T1 == DEFAUL )
    {
        SDL_DestroyTexture( Tex1 );
        Tex1 = loadFromRenderedText( gRenderer, "Play Game", gFont, gColor1 );
    }
        if( T2 == DEFAUL )
    {
        SDL_DestroyTexture( Tex2 );
        Tex2 = loadFromRenderedText( gRenderer, "Exit Game", gFont, gColor1 );
    }

    if( T1 == MOUS )
    {
        SDL_DestroyTexture( Tex1 );
        Tex1 = loadFromRenderedText( gRenderer, "Play Game", gFont, gColor2 );
//        std::cout << 1;
    }
    if( T2 == MOUS )
    {
        SDL_DestroyTexture( Tex2 );
        Tex2 = loadFromRenderedText( gRenderer, "Exit Game", gFont, gColor2 );
    }


    if( T1 == CLIC )
    {
        exit = true;
    }
    else
        if( T2 == CLIC )
    {
        exit = true;
        out = true;
    }
}

bool menu::CheckEventClic( SDL_Renderer* gRenderer, SDL_Event e )
{
    MenuStatus T1, T2;

    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT )
        {
            exit = true;
            out = true;
        }

        T1 = handleEvent( gRenderer, e, rec1 );
        T2 = handleEvent( gRenderer, e, rec2 );
    }


    if( T1 == CLIC )
    {
        exit = true;
        return true;
    }
    else
        if( T2 == CLIC )
    {
        exit = true;
        out = true;
        return true;
    }
    return false;
}

bool menu::CheckExit()
{
    return (exit||out);
}
