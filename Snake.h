#ifndef SNAKE_H
#define SNAKE_H

#include "includes.h"

class SnakeBody{
private:
    typedef std::string::size_type sType;

public:
    SnakeBody(sType x, sType y) : _cX(x), _cY(y), _pX(x), _pY(y){}
    sType _cX, _cY;
    // Needs implementing
    sType _pX, _pY;
};

class SnakeHead{
private:
    typedef std::string::size_type sType;

public:
    SnakeHead(std::string *str, sType x, sType y, sType width, sType height) : _screen(str), _screenWidth(width), _screenHeight(height) {
        if(x > 1 && x < _screenWidth){
            _cX = x;
            _pX = x-1;
        }else{
            std::cout << "OUT OF BOUNCE.\n";
            std::cout << "When Initializing the position of the SnakeHead, Make sure that it has 1 more space on his left side";
        }
        if(y > 0 && y < _screenWidth){
            _cY = y;
            _pY = y;
        }else{
            std::cout << "OUT OF BOUNCE.\n";
            std::cout << "When Initializing the position of the SnakeHead, Make sure that it has 1 more space on his left side (for X)";
        }
        _screen->operator[](x+(y)+(_screenWidth*y)) = 'P';
        createBody();
    }
public:
    void createBody(){
        srand(time(0));
        auto xRand = (rand()%(_screenWidth-2))+1;
        auto yRand = (rand()%(_screenHeight-2))+1;
        auto newBody = new SnakeBody(xRand, yRand);
        _uSnakeBody.push_back(newBody);
        _screen->operator[](xRand+(yRand)+(_screenWidth*yRand)) = 'O';
    }
    void moveUp(){
        move(_cX, _cY-1);
    }
    void moveLeft(){
        move(_cX-1, _cY);
    }
    void moveDown(){
        move(_cX, _cY+1);
    }
    void moveRight(){
        move(_cX+1, _cY);
    }

    void checkAttachForBody(){
        auto size = _uSnakeBody.size();
        int x = 0,
            y = 0,
            i = 0;
        auto iterator_uSnakeBody = _uSnakeBody.begin();
        bool isTrue = false;
        for(; i < size; ++i, ++iterator_uSnakeBody){
            int tempX = _uSnakeBody[i]->_cX,
                tempY = _uSnakeBody[i]->_cY;
            if(tempX == _cX && tempY == _cY){
                x = tempX;
                y = tempY;
                isTrue = true;
                break;
            }
        }
        if(isTrue){
            attach(_uSnakeBody[i]);
            uDetach(iterator_uSnakeBody);
            createBody();
        }
    }
private:
    // changes _cY
    void move(sType x, sType y){

        sType prevX = _cX, prevY = _cY;

        // change the previous position
        _pX = prevX; _pY = prevY;

        // move the position
        moveInScreen(_cX, _cY, x, y, 'P');

        // update the current position 
        _cX = x; _cY = y;
        
        auto size = _aSnakeBody.size();
        for(sType i = 0; i < size; ++i){
            // get the current position of the current body
            sType &cBodyX = _aSnakeBody[i]->_cX;
            sType &cBodyY = _aSnakeBody[i]->_cY;

            // move the position of the current body to the previous position of either the head or the body in front of it
            moveInScreen(cBodyX, cBodyY, prevX, prevY, 'O');

            // create a temporary variable for the previous value of 'x' and 'y'
            int tempPrevX = prevX, tempPrevY = prevY;

            // make the previous value of 'x' and 'y' be equal to the current ("previous" since we move it) 'x' and 'y' of the current body
            prevX = cBodyX; prevY = cBodyY;

            // make the value of 'x' and 'y' inside of the current body be equal to the previous value it is at
            cBodyX = tempPrevX; cBodyY = tempPrevY;
        }
    }
    void attach(SnakeBody *body){
        // TODO: Make sure that when you're going to attach it, it'll be spawned at the end of the tail
        // change the position relative to the last body position
        if(_aSnakeBody.empty()){
            body->_cX = _pX;
            body->_cY = _pY;
        }else{
            auto beforeLast = _aSnakeBody.size() - 1;
            auto tempX = _aSnakeBody[beforeLast]->_pX, 
                 tempY = _aSnakeBody[beforeLast]->_pY;
            body->_cX = tempX;
            body->_cY = tempY;
            body->_pX = tempX;
            body->_pY = tempY;
        }
        _aSnakeBody.push_back(body);
    }
    void uDetach(std::vector<SnakeBody*>::iterator body){
        _uSnakeBody.erase(body);
    }
private:
    void moveInScreen(sType pX, sType pY, sType nX, sType nY, char chr){
        (*_screen)[nX+(nY)+(_screenWidth*nY)] = chr;
        (*_screen)[pX+(pY)+(_screenWidth*pY)] = ' ';
    }

private:
    std::string *_screen;
    std::vector<SnakeBody*> _aSnakeBody; // attached
    std::vector<SnakeBody*> _uSnakeBody; // unattached
    sType _cX, _cY;
    sType _pX, _pY;
    sType _screenWidth, _screenHeight;
};

#endif // SNAKE_H