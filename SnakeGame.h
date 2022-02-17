#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "includes.h"
#include "Snake.h"

class SnakeGame{
private:
    typedef std::string::size_type sType;

public: // Constructors
    SnakeGame(){
        _screenWidth = 20;
        _screenHeight = 10;
        setupMap();
        _head = new SnakeHead(&_screen, 2, 1, _screenWidth, _screenHeight);
    }

public:
    void initGame(){
        
        sType *keyboardInput = new sType(4);
        // Printing Thread
        std::thread printThread(&printScreen, this);
        printThread.detach();

        // MovementThread
        std::thread changeMovementThread(&changeMovement, this, keyboardInput);
        changeMovementThread.detach();

        std::thread moveSnakeThread(&moveSnake, this, keyboardInput);
        moveSnakeThread.detach();

        while(*keyboardInput != 5){
        }
        inGame = false;
    }

private: // screen stuffs
    void printScreen(){
        while(inGame){
            std::cout << _screen;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            system("cls");
        }
    }

private: // movements
    void changeMovement(sType *keyboardInput){
        while(inGame){
            char keyIn = _getwch();
            if(keyIn == 'w'){
                *keyboardInput = 1;
            }else if(keyIn == 'a'){
                *keyboardInput = 2;
            }else if(keyIn == 's'){
                *keyboardInput = 3;
            }else if(keyIn == 'd'){
                *keyboardInput = 4;
            }else if(keyIn == 'x'){
                *keyboardInput = 5;
                break;
            }
            std::cout << *keyboardInput << std::endl;
        }
    }
    void moveSnake(sType *keyboardInput){
        while(inGame){
            if(*keyboardInput == 1){
                _head->moveUp();
            }else if(*keyboardInput == 2){
                _head->moveLeft();
            }else if(*keyboardInput == 3){
                _head->moveDown();
            }else if(*keyboardInput == 4){
                _head->moveRight();
            }
            if(_head->checkAttachForBody()){
                _head->createBody();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
private:
    void setupMap(){
        _screen += std::string(_screenWidth, '#') + '\n';
        for(int i = 0; i < _screenHeight-2; ++i){
            _screen += '#' + std::string(_screenWidth-2, ' ') + '#' + '\n';
        }
        _screen += std::string(_screenWidth, '#') + '\n';
    }

private:
    bool inGame = true;
    sType _screenHeight, _screenWidth;
    SnakeHead *_head;
    std::string _screen;
};



#endif // SNAKE_GAME_H