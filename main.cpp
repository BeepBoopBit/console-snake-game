#include "includes.h"
#include "Snake.h"

int main(){
    std::string _screen;
    for(int i = 0; i < 6; ++i){
        _screen += std::string(6, '#') + '\n';
    }
    SnakeHead head(_screen,4,1,6,6);
    SnakeBody *body1 = new SnakeBody(3,1);
    SnakeBody *body2 = new SnakeBody(2,1);

    return 0;
}