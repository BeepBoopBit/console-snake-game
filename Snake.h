#ifndef SNAKE_H
#define SNAKE_H

#include "includes.h"

class SnakeBody{
private:
    typedef std::string::size_type sType;

public:
    SnakeBody(sType x, sType y) : _cX(x), _cY(y){}
    sType _cX, _cY;
};

class SnakeHead{
private:
    typedef std::string::size_type sType;

public:
    SnakeHead(std::string &str, sType x, sType y, sType width, sType height) : _screen(&str), _cX(x), _cY(y), _screenWidth(width), _screenHeight(height) {}
    void move(sType x, sType y){
        // move head
        //std::cout << "Head:\n";
        
        //std::cout << "cX: " << _cX << '\n';
        //std::cout << "cY: " << _cY << '\n';
        //std::cout << "nX: " << x << '\n' ;
        //std::cout << "nY: " << y << '\n' ;

        sType prevX = _cX, prevY = _cY;
        moveInScreen(_cX, _cY, x, y, 'P');
        _cX = x; _cY = y;
        
        auto size = _snakeBody.size();
        for(sType i = 0; i < size; ++i){
            //std::cout << "Body:[" << i << "]\n";
            sType &cBodyX = _snakeBody[i]->_cX;
            sType &cBodyY = _snakeBody[i]->_cY;
            //std::cout << "cBodyX: " << cBodyX << '\n';
            //std::cout << "cBodyY: " << cBodyY << '\n';
            moveInScreen(cBodyX, cBodyY, prevX, prevY, 'O');
            int tempPrevX = prevX, tempPrevY = prevY;
            prevX = cBodyX; prevY = cBodyY;
            cBodyX = tempPrevX; cBodyY = tempPrevY;
            //std::cout << "nBodyX: " << cBodyX << '\n';
            //std::cout << "nBodyY: " << cBodyY << '\n';
        }
    }
    void attach(SnakeBody *body){
        _snakeBody.push_back(body);
    }
private:
    void moveInScreen(sType pX, sType pY, sType nX, sType nY, char chr){
        (*_screen)[nX+(nY)+(_screenWidth*nY)] = chr;
        (*_screen)[pX+(pY)+(_screenWidth*pY)] = ' ';
    }

private:
    std::string *_screen;
    std::vector<SnakeBody*> _snakeBody;
    sType _cX, _cY;
    sType _screenWidth, _screenHeight;
};

#endif // SNAKE_H