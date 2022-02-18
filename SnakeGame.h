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

        // Movement Threads
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
            showScore();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            system("cls");
        }
    }

private: // movements
    void changeMovement(sType *keyboardInput){
        while(inGame){
            char keyIn = _getwch();
            if(keyIn == 'w' && *keyboardInput != 3){
                *keyboardInput = 1;
            }else if(keyIn == 'a' && *keyboardInput != 4){
                *keyboardInput = 2;
            }else if(keyIn == 's' && *keyboardInput != 1){
                *keyboardInput = 3;
            }else if(keyIn == 'd' && *keyboardInput != 2){
                *keyboardInput = 4;
            }else if(keyIn == 'x' ){
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
                ++_score;
            }
            if(_head->checkOutOfBounce()){
                gameover();
            }
            if(_head->checkBodyCollision()){
                gameover();
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
    void gameover(){
        inGame = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "GAMEOVER!! Your Score is: " << _score << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        saveScore();
        showLeadeboard();
        system("pause");
        exit(0);
    }
    void showScore(){
        moveCursor(_screenWidth+2, 1);
        std::cout << "SCORE: " << _score;
        moveCursor(1, _screenHeight+2);
    }
    void moveCursor(int x, int y){
        std::cout << "\033[" << y << ';' << x << "H"; 
    }
    
    // not yet done
    void showLeadeboard(){
        std::ifstream iFile("scoreboard.txt");
        if(iFile.is_open()){
            std::string tempStr;
            while(std::getline(iFile, tempStr)){
                std::cout << tempStr << std::endl;
            }
        }else{
            std::cout << "scoreboard.txt isn't found" << std::endl;
            exit(-1);
        }
    }
    void saveScore(){
        std::ifstream iFile("scoreboard.txt");
        if(iFile.is_open()){
            std::cout << "Enter your name: ";
            std::string username;
            std::getline(std::cin, username);

            // separate word, separator, and number
            std::vector<std::string> names = {username};
            std::vector<int> scores = {_score};

            std::string tempNames,separator;
            int tempScores;
            // assumes that scoreboard.txt is in correct order
            while(iFile >> tempNames >> separator >> tempScores){
                names.push_back(tempNames);
                scores.push_back(tempScores);
            }

            // sort vector
            auto scoreSize = scores.size();
            for(int i = 0; i < scoreSize; ++i){
                for(int j = 0; j < scoreSize-i-1; ++j){
                    if(scores[j] < scores[j+1]){
                        std::swap(scores[j], scores[j+1]);
                        std::swap(names[j], names[j+1]);
                    }
                }
            }

            std::ofstream oFile("scoreboard.txt");
            if(oFile.is_open()){
                for(int i = 0; i < names.size(); ++i){
                    oFile << names[i] << " : " << scores[i] << '\n';
                }
            }else{
                std::cout << "scoreboard.txt isn't found" << std::endl;
                exit(-1);
            }
        }else{
        }
    }
private:
    bool inGame = true;
    sType _screenHeight, _screenWidth;
    SnakeHead *_head;
    std::string _screen;
    int _score = 0;
};



#endif // SNAKE_GAME_H