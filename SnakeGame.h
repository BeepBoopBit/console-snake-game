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
        _head = new SnakeHead(_screen, 2, 1, _screenWidth, _screenHeight);
    }

public:
    void initGame(){

        // create initial body
        _head->createBody();

        setupMap();

        // --- Set-up Threads --- //
        // printing
        std::thread tPrintScreen(&printScreen, this);
        tPrintScreen.detach();

        // keyboard Events
        sType *keyboardPressed = new sType(4);
        std::thread tKeyboardEvent(&keyboardEvent, this, keyboardPressed);
        tKeyboardEvent.detach();

        // moving + checking if there is something adjacent
        std::thread tMoveHead(&moveHead, this, keyboardPressed);
        tMoveHead.detach();

        while(*keyboardPressed != 'x'){
        }
        inGame = false;
    }


private: // movements
    void printScreen(){
        while(inGame){
            std::cout << _screen;
            // to lower the amount of printing
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // kind of slow
            system("cls");
        }
    }
    void keyboardEvent(sType *keyboardPressed){ 
        while(inGame){
            auto keyEvent = _getwch();
            if(keyEvent == 'w'){
                *keyboardPressed = 1;
            }else if(keyEvent == 'a'){
                *keyboardPressed = 2;
            }else if(keyEvent == 's'){
                *keyboardPressed = 3;
            }else if(keyEvent == 'd'){
                *keyboardPressed = 4;
            }
        }
    }
    void moveHead(sType *keyboardPressed){
        while(inGame){
            if(*keyboardPressed == 1){
                _head->moveUp();
            }else if(*keyboardPressed == 2){
                _head->moveLeft();
            }else if(*keyboardPressed == 3){
                _head->moveDown();
            }else if(*keyboardPressed == 4){
                _head->moveRight();
            }
            if(_head->checkAttachForBody()){
                // create new body
                _head->createBody();
            } 
        }
    }

private:
    void setupMap(){
        for(int i = 0; i < _screenHeight; ++i){
            _screen = std::string(_screenWidth, ' ') + '\n';
        }
    }

private:
    bool inGame = true;
    sType _screenHeight, _screenWidth;
    SnakeHead *_head;
    std::string _screen;
};



#endif // SNAKE_GAME_H