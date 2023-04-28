#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>

enum Tus
{
    DEFAULT,
    MOUSE,
    CLICK,
    TOTAL
};

class MenuSize
{
    public:

        //Khởi tạo
        MenuSize();

        //Khởi tạo ảnh
        void initTex( SDL_Renderer* gRenderer );

        //Vẽ mọi thứ
        void renderTex( SDL_Renderer* gRenderer );

        //Kiểm soát event
        Tus handleEvent( SDL_Renderer* gRenderer, SDL_Event e, SDL_Rect R );

        //Xử lý event
        void CheckEvent( SDL_Renderer* gRenderer, SDL_Event e );
        
        //Xử lý sound event
        bool CheckEventClic( SDL_Renderer* gRenderer, SDL_Event e );

        //Đã thoát ?
        bool CheckExit();

        //Xoá
        void Clear();

        //Khởi tạo lại
        void reset();

        //Thay đổi
        int Change = 0;

        //Thoát cả game
        bool out;

    private:

        SDL_Texture *Tex1, *Tex2, *Tex3, *Tex4;
        SDL_Texture* Tex;

        bool exit;
};
