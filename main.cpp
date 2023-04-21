#include "init.h"
#include "picksize.h"
#include "menu.h"

//Điều chỉnh bàn chơi
int change = 0;

//Cửa sổ game
SDL_Window* gWindow;

//Màn hình game
SDL_Renderer* gRenderer;

//Dot
SDL_Texture* dot = NULL;

// background
SDL_Texture* background = NULL;
SDL_Texture* backgroundPickSize = NULL;
SDL_Texture* backgroundGame = NULL;

//Các ô
SDL_Texture* cell[3];

//Dòng kẻ
SDL_Texture* line[ Total ];

//Có đường kẻ hay không
bool ver[ CELL_NUMW+1 ][ CELL_NUMH+1 ];//dọc
bool hor[ CELL_NUMW+1 ][ CELL_NUMH+1 ];//ngang

//Trạng thái ngang và dọc
Status eHorizontal[ CELL_NUMW+2 ][ CELL_NUMH+2 ];//ngang
Status eVertical[ CELL_NUMW+2 ][ CELL_NUMH+2 ];//dọc

//Lượt người chơi
int turn = 1;

//đi tiếp
bool again = false;

//ô đấy đã có X hay O chưa
bool block[ CELL_NUMW+1 ][ CELL_NUMH+1 ];

//điểm từng người chơi
int Score1, Score2;

MenuSize m;
menu Me;

//Khởi tạo cửa sổ
void initWindow()
{
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Dot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				}
			}
		}
	}
}

//Khởi tạo các ảnh
void initTexture()
{
    dot = loadTexture( gRenderer, "Dot1.png" );
	
    background = loadTexture(gRenderer, "background1.png");
    backgroundPickSize = loadTexture(gRenderer, "background2.png");
    backgroundGame = loadTexture(gRenderer, "background3.png");	

    line[ Default ] = NULL;
    line[ Mousemotion ] = loadTexture( gRenderer, "Mousemotion.png" );

    cell[0] = NULL;
    TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 48 );
    SDL_Color gColor = { 0, 200, 0 };
    cell[1] = loadFromRenderedText( gRenderer, "X", gFont, gColor ); //Đánh dấu ô của người chơi x
    SDL_Color ggColor = { 200, 0, 0 };
    cell[2] = loadFromRenderedText( gRenderer, "O", gFont, ggColor ); //Đánh dấu ô của người chơi o
}

//Đóng lại mọi thứ
void close()
{
    for(int i=0; i<Total; i++)
    {
        SDL_DestroyTexture( line[i] );
        line[i] = NULL;
    }
    SDL_DestroyTexture( dot );
    dot = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

//Vẽ các chấm
void renderDot()
{
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    for( int i=change + 1; i<=CELL_NUMW - change; i++ )
    {
        for( int j=change + 1; j<=CELL_NUMH - change; j++ )
        {
            SDL_Rect RectDot = { i*CELL_WIDTH-15, j*CELL_HEIGHT-15, DOT_WIDTH, DOT_HEIGHT };
            SDL_RenderCopy( gRenderer, dot, NULL, &RectDot );
//            SDL_RenderDrawPoint( gRenderer, i*CELL_WIDTH, j*CELL_HEIGHT );
        }
    }
}

//event khi ngang
Status handleEvent1( SDL_Event e, int i, int j )
{
    Status currentEvent = Default;
    //If mouse event happened
        if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

            //Check if mouse is in button
            bool inside = true;

            //Mouse is left of the button
            if( y < i*CELL_HEIGHT-2 )
            {
                inside = false;
            }
            //Mouse is right of the button
            else if( y > i*CELL_HEIGHT+2 )
            {
                inside = false;
            }
            //Mouse above the button
            else if( x < j*CELL_WIDTH+2 )
            {
                inside = false;
            }
            //Mouse below the button
            else if( x > (j+1)*CELL_WIDTH-2 )
            {
                inside = false;
            }

            //Mouse is outside button
            if( !inside )
            {
                if(currentEvent == Mousemotion)
                {
                    currentEvent = Default;
                }
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                if( currentEvent == Default || currentEvent == Mousemotion )
                    switch( e.type )
                    {
                        case SDL_MOUSEMOTION:
                        {
                            currentEvent = Mousemotion;
                            break;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if( turn == 1 )
                            {
                                if( !again )
                                    turn = 2;
                            }
                            else
                                if( !again )
                                    turn = 1;

                            hor[ i ][ j ] = true;
                            currentEvent = Line;
                            break;
                        }
                    }
            }
        }
    return currentEvent;
}

//event khi dọc
Status handleEvent2( SDL_Event e, int i, int j)
{
    Status currentEvent = Default;
    //If mouse event happened
        if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

            //Check if mouse is in button
            bool inside = true;

            //Mouse is left of the button
            if( y < i*CELL_HEIGHT+2 )
            {
                inside = false;
            }
            //Mouse is right of the button
            else if( y > (i+1)*CELL_HEIGHT-2 )
            {
                inside = false;
            }
            //Mouse above the button
            else if( x < j*CELL_WIDTH-2 )
            {
                inside = false;
            }
            //Mouse below the button
            else if( x > j*CELL_WIDTH+2 )
            {
                inside = false;
            }

            //Mouse is outside button
            if( !inside )
            {
                if(currentEvent == Mousemotion)
                {
                    currentEvent = Default;
                }
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                if( currentEvent == Default || currentEvent == Mousemotion )
                    switch( e.type )
                    {
                        case SDL_MOUSEMOTION:
                        {
                            currentEvent = Mousemotion;
                            break;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if( turn == 1 )
                            {
                                turn = 2;
                            }
                            else
                                turn = 1;

                            ver[ i ][ j ] = true;
                            currentEvent = Line;
                            break;
                        }
                    }
            }
        }
    return currentEvent;
}

//Vẽ hình ảnh dòng kẻ
void renderLine( int i, int j, Status ngang, Status doc )
{
    //Xét ngang
    if( ngang == Mousemotion )
    {
        SDL_Rect demo = { j*CELL_WIDTH, i*CELL_HEIGHT-1, CELL_WIDTH, 3 };
        SDL_RenderCopy( gRenderer, line[ ngang ], NULL, &demo );
    }
    else
        if( ngang == Line )
    {
        SDL_RenderDrawLine( gRenderer, j*CELL_WIDTH, i*CELL_HEIGHT, (j+1)*CELL_WIDTH, i*CELL_HEIGHT );
    }

    //Xét dọc
    if( doc == Mousemotion )
    {
        SDL_Rect demo = { j*CELL_WIDTH-1, i*CELL_HEIGHT, 3, CELL_HEIGHT };
        SDL_RenderCopy( gRenderer, line[ doc ], NULL, &demo );
    }
    else
        if( doc == Line )
    {
        SDL_RenderDrawLine( gRenderer, j*CELL_WIDTH, i*CELL_HEIGHT, j*CELL_WIDTH, (i+1)*CELL_HEIGHT );
    }
}

//Kiểm tra ô vuông i j
bool CheckCell( int i, int j )
{
    if( !ver[i][j] )
        return false;

    if( !hor[i][j] )
        return false;

    if( !hor[i+1][j] )
        return false;

    if( !ver[i][j+1] )
        return false;
    return true;
}

//Trạng thái ô
int C[ CELL_NUMW+1 ][ CELL_NUMH+1 ];

//Kiểm tra cả bàn chơi
void CheckBoard()
{
    bool ok = false;
    int danhdau = 0;
    for(int i=change + 1; i<CELL_NUMW - change; i++)
    {
        for(int j=change + 1; j<CELL_NUMH - change; j++)
        {
            if( CheckCell( i, j ) && !block[i][j] )
            {
	        if(danhdau == 0){
                if( turn == 1 )
                {
                    turn = 2;
                }
                    else
                turn = 1;
		danhdau = 1;
		}

                C[i][j] = turn;
                block[i][j] = true;
                again = true;
                ok = true;

                if( turn == 1 )
                    Score1++;
                else
                    Score2++;
            }

            SDL_Rect rect = { j*CELL_HEIGHT+6, i*CELL_WIDTH+8, CELL_WIDTH-10, CELL_HEIGHT-10 };
            SDL_RenderCopy( gRenderer, cell[ C[i][j] ], NULL, &rect );
        }
    }
    if( !ok )
        again = false;
}

//Vẽ màu cho bàn chơi
void drawBoard()
{
    //Rect bàn
    SDL_Rect BoardRect = { CELL_WIDTH/2*(change*2+1), CELL_HEIGHT/2*(change*2+1), CELL_WIDTH*(10-change*2), CELL_HEIGHT*(10-change*2) };
    //Màu bàn
    SDL_SetRenderDrawColor( gRenderer, 0xCC, 0xFF0, 0x99, 0xFF );
    //Vẽ bàn
    SDL_RenderFillRect( gRenderer, &BoardRect );
    //Màu viền bàn
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
    //Vẽ viền bàn
    SDL_RenderDrawRect( gRenderer, &BoardRect );
}

//Vẽ Menu
void drawMenu()
{
    //740 440
    //40 40
    //10 10

    //Vẽ menu:
    //Rect cái menu
    SDL_Rect MenuRect = { CELL_WIDTH*12, CELL_HEIGHT/2, CELL_WIDTH*6, CELL_HEIGHT*10 };
    //Màu menu
    SDL_SetRenderDrawColor( gRenderer, 0xCC, 0xCC, 0x99, 0xFF );
    //Vẽ menu
    SDL_RenderFillRect( gRenderer, &MenuRect );

    //Màu viền Menu
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
    //Vẽ viền Menu
    SDL_RenderDrawRect( gRenderer, &MenuRect );

    //Vẽ các ô vuông khác
    SDL_Rect MENUturn = { CELL_WIDTH*13+10, CELL_HEIGHT*5-20, CELL_WIDTH*4-20, CELL_HEIGHT };
    SDL_RenderDrawRect( gRenderer, &MENUturn );

    SDL_Rect MENUnewgame = { CELL_WIDTH*13, CELL_HEIGHT*6, CELL_WIDTH*4, CELL_HEIGHT*2-10 };
    SDL_RenderDrawRect( gRenderer, &MENUnewgame );

    SDL_Rect MENUexit = { CELL_WIDTH*13, CELL_HEIGHT*8+10, CELL_WIDTH*4, CELL_HEIGHT*2-10 };
    SDL_RenderDrawRect( gRenderer, &MENUexit );
}

SDL_Texture* Left;
SDL_Texture* Right;
SDL_Texture* Middle;
SDL_Texture* Newgame;
SDL_Texture* Exit;

SDL_Texture* Menu;
SDL_Texture* Turn1;
SDL_Texture* Turn2;
SDL_Texture* win1;
SDL_Texture* win2;

void initText()
{
        //Font chữ
	TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 80 );
	TTF_Font* gFontTurn = TTF_OpenFont( "Menu.ttf", 40 );
	
	//Màu chữ
	SDL_Color textColor = { 70, 70, 70 };

	Newgame = loadFromRenderedText( gRenderer, "New Game", gFont, textColor );
	Exit = loadFromRenderedText( gRenderer, "Exit", gFont, textColor );

	Menu = loadFromRenderedText( gRenderer, "MENU", gFont, textColor );
	Turn1 = loadFromRenderedText( gRenderer, "Turn: X ", gFontTurn, textColor );
	Turn2 = loadFromRenderedText( gRenderer, "Turn: O ", gFontTurn, textColor );
	
	win1 = loadTexture(gRenderer,"winnerX.png");
	win2 = loadTexture(gRenderer, "winnerO.png");
}

void renderText()
{
    SDL_Rect rectMENU = { CELL_WIDTH*13, CELL_HEIGHT-5, CELL_WIDTH*4, CELL_HEIGHT*2-10 };
    SDL_RenderCopy( gRenderer, Menu, NULL, &rectMENU );
    
    if( turn ==1) {SDL_Rect rectTurn1 = { CELL_WIDTH*13, CELL_HEIGHT*3, CELL_WIDTH*4, CELL_HEIGHT };
    SDL_RenderCopy( gRenderer, Turn1, NULL, &rectTurn1 );} else {
    SDL_Rect rectTurn2 = { CELL_WIDTH*13, CELL_HEIGHT*3, CELL_WIDTH*4, CELL_HEIGHT };
    SDL_RenderCopy( gRenderer, Turn2, NULL, &rectTurn2 );}
    
    if((Score1 + Score2) == (CELL_NUMW-change*2-1)*(CELL_NUMH-change*2-1)){
            SDL_Rect rectScore = { 0, 200, 480, 50 };
            if(Score1 > Score2) SDL_RenderCopy(gRenderer, win1, NULL, &rectScore);
            else SDL_RenderCopy(gRenderer, win2, NULL, &rectScore);
    }
    
    SDL_Rect rectnew = { CELL_WIDTH*14-20, CELL_HEIGHT*6+15, CELL_WIDTH*3, CELL_HEIGHT };
    SDL_RenderCopy( gRenderer, Newgame, NULL, &rectnew );

    SDL_Rect rectout = { CELL_WIDTH*15-25, CELL_HEIGHT*9-15, CELL_WIDTH+20, CELL_HEIGHT };
    SDL_RenderCopy( gRenderer, Exit, NULL, &rectout );
}

void NewGame()
{
//    C[i][j] = turn;
//    block[i][j] = true;
//    again = true;
    for(int i=1; i<=CELL_NUMW; i++)
    {
        for(int j=1; j<=CELL_NUMH; j++)
        {
            eHorizontal[i][j] = Default;
            eVertical[i][j] = Default;
            ver[i][j] = false;
            hor[i][j] = false;
            C[i][j] = 0;
            block[i][j] = false;
        }
    }



    again = false;
    turn = 1;
    Score1 = 0;
    Score2 = 0;
}

enum MainStatus
{
    nul,
    unnul,
    press,
    total
};

SDL_Texture* Menunew[ total ];
SDL_Texture* Menuout[ total ];

void initMainText()
{
    Menunew[ nul ] = NULL;
    Menunew[ unnul ] = loadTexture( gRenderer, "Mousemotion.png" );
    Menunew[ press ] = NULL;

    Menuout[ nul ] = NULL;
    Menuout[ unnul ] = loadTexture( gRenderer, "Mousemotion.png" );
    Menuout[ press ] = NULL;
}

MainStatus handleEvent( SDL_Event e, SDL_Rect R )
{
    MainStatus currentEvent = nul;
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
                if(currentEvent == unnul)
                {
                    currentEvent = nul;
                }
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                if( currentEvent == nul || currentEvent == unnul )
                    switch( e.type )
                    {
                        case SDL_MOUSEMOTION:
                        {
                            currentEvent = unnul;
                            break;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        {
                            currentEvent = press;
                            break;
                        }
                    }
            }
        }
    return currentEvent;
}

SDL_Rect rectnew = { CELL_WIDTH*13+1, CELL_HEIGHT*6+1, CELL_WIDTH*4-2, CELL_HEIGHT*2-12 };
SDL_Rect rectout = { CELL_WIDTH*13+1, CELL_HEIGHT*8+11, CELL_WIDTH*4-2, CELL_HEIGHT*2-12 };

void renderMainMenu( MainStatus M1, MainStatus M2 )
{
    SDL_RenderCopy( gRenderer, Menunew[ M1 ], NULL, &rectnew );
    SDL_RenderCopy( gRenderer, Menunew[ M2 ], NULL, &rectout );
}

void FirstMenu( SDL_Event e )
{
    while( !Me.CheckExit() )
    {
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear( gRenderer );

	SDL_RenderCopy(gRenderer,background,NULL,NULL);
    
        Me.CheckEvent( gRenderer, e );
        Me.renderTex( gRenderer );

        SDL_RenderPresent( gRenderer );
    }
    SDL_Delay(300);
}

void Picksize( SDL_Event e )
{
    m.reset();
    while( !m.CheckExit() )
    {
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear( gRenderer );

        SDL_RenderCopy(gRenderer,backgroundPickSize,NULL,NULL);
	
        m.CheckEvent( gRenderer, e );
        m.renderTex( gRenderer );

        SDL_RenderPresent( gRenderer );
    }
}

int main( int argc, char** argv )
{
    initWindow();
    initTexture();
    initText();

    SDL_Event e1, e2, e;

    Me.initTex( gRenderer );
    FirstMenu( e1 );

    m.out = Me.out;
    m.initTex( gRenderer );
    Picksize( e2 );

    bool quit = m.out;
    change = m.Change;

    NewGame();

    MainStatus Ms1=nul, Ms2=nul;

    initMainText();

    while( !quit )
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            Ms1 = handleEvent( e, rectnew );
            Ms2 = handleEvent( e, rectout );

            for(int i=change + 1; i<=CELL_NUMW - change; i++)
            {
                for(int j=change + 1; j<CELL_NUMH - change; j++)
                {
                    if( eHorizontal[i][j] != Line )
                    eHorizontal[i][j] = handleEvent1( e, i, j );
                }
            }
            for(int i=change + 1; i<CELL_NUMW - change; i++)
            {
                for(int j=change + 1; j<=CELL_NUMH - change; j++)
                {
                    if( eVertical[i][j] != Line )
                    eVertical[i][j] = handleEvent2( e, i, j );
                }
            }
        }

        //Xoá màn hình bằng màu trắng
        SDL_SetRenderDrawColor( gRenderer, 77, 77, 77, 0xFF );
        SDL_RenderClear( gRenderer );

        // Vẽ background của bàn chơi
        SDL_RenderCopy(gRenderer,backgroundGame,NULL,NULL);
	
	drawMenu();
	
        drawBoard();

        CheckBoard();

        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0 , 0 );
        for(int i=change + 1; i<=CELL_NUMW - change; i++)
            {
                for(int j=change + 1; j<=CELL_NUMH - change; j++)
            {
                renderLine( i, j, eHorizontal[i][j], eVertical[i][j] );
            }
        }

        renderDot();
        //drawMenu();
        renderMainMenu( Ms1, Ms2 );
        renderText();

        //Update màn hình
        SDL_RenderPresent( gRenderer );

        if( Ms1 == press )
        {
            Picksize( e2 );
            NewGame();
            change = m.Change;
            quit = quit || m.out;
            Ms1 = nul;
            Ms2 = nul;
        }
        else if( Ms2 == press )
        {
            quit = true;
        }
    }

    close();
}
