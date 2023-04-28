#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

enum MenuStatus
{
    DEFAUL,
    MOUS,
    CLIC,
    TOTA
};

class menu
{
    public:

        //Khởi tạo
        menu();

        //Khởi tạo ảnh
        void initTex( SDL_Renderer* gRenderer );

        //Vẽ mọi thứ
        void renderTex( SDL_Renderer* gRenderer );

        //Kiểm soát event
        MenuStatus handleEvent( SDL_Renderer* gRenderer, SDL_Event e, SDL_Rect R );

        //Xử lý event
        void CheckEvent( SDL_Renderer* gRenderer, SDL_Event e );
        
        //Xử lý sound event
        bool CheckEventClic( SDL_Renderer* gRenderer, SDL_Event e );

        //Đã thoát ?
        bool CheckExit();

        //Thoát cả game
        bool out;

    private:

        SDL_Texture *Tex1, *Tex2;
        SDL_Texture* Tex;
        bool ok = true;
        bool exit;
};
