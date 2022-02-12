#include "includes.h"
#include "Snake.h"

int main(){
    std::string _screen;
    for(int i = 0; i < 5; ++i){
        _screen += std::string(10, ' ') + '\n';
    }
    SnakeHead head(_screen,4,1,5,5);
    SnakeBody *body1 = new SnakeBody(3,1);
    SnakeBody *body2 = new SnakeBody(2,1);
    head.attach(body1);
    head.attach(body2);
    head.move(4,1);

    return 0;
}