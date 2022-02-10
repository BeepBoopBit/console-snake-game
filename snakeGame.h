#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "includes.h"

class SnakeGame{
private:
    typedef std::string::size_type sType;
public: // constructors
    SnakeGame(){
        _screenHeight = 50;
        _screenWidth = 100;
        setupMap();
    }
    SnakeGame(sType width, sType height){
        _screenHeight = height;
        _screenWidth = width;
        setupMap();
    }
    // width will be 2*height
    SnakeGame(sType height){
        _screenHeight = height;
        _screenWidth = 2*height;
        setupMap();
    }

public:
    void initGame(){
        // setupMap();
        initSnake();
        // deamon thread for movement
        int movementValue = 4;
        std::thread thread01(&changeMovement, movementValue);
        thread01.detach();
    }
    void printMap(){
        std::cout << _screen;
    }

private: // snake
    void initSnake(){
        // generate random position
        auto tempPos = generateRandomPosition();
        _screen[tempPos.first+((tempPos.second-1)*_screenWidth)] = 'P';
        SnakeItself.push_back({'P',{tempPos.first,tempPos.second}});
    }
    void moveSnake(int direction){
    }
private: // movement
    void changeMovement(int &varb){
        while(true){
            char keyboardEvent = _getwch();
            if(keyboardEvent == 'w'){
                varb = 1;
            }else if(keyboardEvent == 'a'){
                varb = 2;
            }else if(keyboardEvent == 's'){
                varb = 3;
            }else if(keyboardEvent == 'd'){
                varb = 4;
            }
        }
    }
    void moveUp(){

    }
private: // utility
    void setupMap(){
        for(int i = 0; i < _screenHeight; ++i){
            _screen += std::string(_screenWidth,' ') + '\n';
        }
    }
    std::pair<int,int> generateRandomPosition(){
        srand(time(0));
        int randX = (rand() % (_screenWidth-1)) + 1,
            randY = (rand() % (_screenHeight-1)) + 1;
        return {randX, randY};
    }
private:
    std::string _screen;
    sType _screenWidth, _screenHeight;
    std::vector<std::pair<char, std::pair<int,int>>> SnakeItself;


};


#endif // SNAKE_GAME_H