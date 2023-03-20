//包含基本结构体信息的头文件
#include "Basic Information.hpp"
#include "Audience Info.hpp"
#include "Admin Info.hpp"

//声明外部函数：欢迎和选择界面部分，详见文件Welcome.c
extern int main_menu();
//#define DEBUG //定义Debug模式
#ifndef DEBUG
//主函数
int main() {
    //确定两个大分支中选择哪一个
    restart:
    int user_choice = main_menu();
    switch (user_choice) {
        case 1:
            //进入观众大分支
            User::main();
            break;
        case 2:
            //进入管理员大分支
            Admin::check();
            Admin::main();
            break;
        case 0:
            exit(1);
        default:
            printf("请输入1-3：");
            goto restart;
    }
    return 0;
}

#else
//DEBUG模式的主函数
#include <SDL.h>
#include <SDL_ttf.h>
#define WIDTH 900
#define HEIGHT 600
typedef struct {
    SDL_Rect draw_rect;    // dimensions of button
    struct {
        Uint8 r, g, b, a;
    } colour;
    bool pressed;
} button_t;
static void button_process_event(button_t *btn, const SDL_Event *ev) {
    // react on mouse click within button rectangle by setting 'pressed'
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
           ev->button.x >= btn->draw_rect.x &&
           ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
           ev->button.y >= btn->draw_rect.y &&
           ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
            btn->pressed = true;
        }
    }
}
static bool button_d(SDL_Renderer *r, button_t *btn) {
    // draw button
    SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
    SDL_RenderFillRect(r, &btn->draw_rect);

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}

int main(int argc, char* argv[]){
    // 初始化
    int quit=0;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        fprintf(stderr, "create window failed: %s\n", SDL_GetError());
        return 1;   // 'error' return status is !0. 1 is good enough
    }
    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {   // renderer creation may fail too
        fprintf(stderr, "create renderer failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* txt = nullptr;
    SDL_Rect rct={0,0,WIDTH,HEIGHT};
    // button state - colour and rectangle
    button_t button={{400,300,100,50},
                           {255,255,255},
                           false};
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // exit loop
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // check if mouse is inside button area
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= button.draw_rect.x && x <= button.draw_rect.x + button.draw_rect.w &&
                    y >= button.draw_rect.y && y <= button.draw_rect.y + button.draw_rect.h) {
                    // set button state to pressed
                    button.pressed = true;
                }
            }
        }
        // draw window and button here
        button_d(renderer,&button);
    }

//
//    // 打开字体文件
//    TTF_Font* font = TTF_OpenFont("/Users/amagicpear/Library/Fonts/HYFengGuKaiTiW.ttf", 32);
//
//    // 设置文本内容和颜色
//    std::string text = "Hello World";
//    SDL_Color color = {255, 255, 255};
//
//    // 创建表面
//    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
//    // 创建纹理
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//
//    // 获取纹理的宽度和高度
//    int w, h;
//    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
//
//    // 设置纹理在窗口中的位置和大小
//    SDL_Rect rect;
//    rect.x = (WIDTH - w) / 2;
//    rect.y = (HEIGHT - h) / 2;
//    rect.w = w;
//    rect.h = h;
//    // 清除渲染器
//    SDL_RenderClear(renderer);
//
//    // 复制纹理到渲染器
//    SDL_RenderCopy(renderer, texture, NULL, &rect);
//
//    // 更新窗口
//    SDL_RenderPresent(renderer);
//

//    // 释放资源
//    SDL_DestroyTexture(texture);
//    SDL_FreeSurface(surface);
//    TTF_CloseFont(font);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
}

#endif