#include "graph.h"
#include "Snake.h"
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iostream>

int main(void) {
    std::ifstream  infile;
    infile.open("bestScore.dat", std::ios::in);
    int bestScore;
    infile >> bestScore;
    infile.close();
    Graph g(bestScore);
    Snake s(g);
    g.graphShow();
    char preDir = Snake::RIGHT;
    while(s.isAlive()) {
        char dir = _getch();
        dir = dir >= 'a' ?  dir - ('a' - 'A') : dir;
        if((dir != Snake::UP && dir != Snake::DOWN && dir != Snake::LEFT && dir != Snake::RIGHT) || 
           dir == Snake::UP && preDir == Snake::DOWN || dir == Snake::DOWN && preDir == Snake::UP ||
           dir == Snake::LEFT && preDir == Snake::RIGHT || dir == Snake::RIGHT && preDir == Snake::LEFT 
        ) {
            dir = preDir;
        }
        preDir = dir;
        do {
            s.snakeMove(g, dir);
            system("cls");
            g.graphShow();
            char* speed = g.getSpeed();
            if(!strcmp(speed, "Slow")) {
                Sleep(Graph::SLOW);
            }
            else if(!strcmp(speed, "Middle")) {
                Sleep(Graph::MIDDLE);
            }
            else {
                Sleep(Graph::QUICK);
            }
        }while(s.isAlive() && !_kbhit());
    }
    int score = g.getScore();
    if(score > bestScore) {
        std::ofstream outfile;
        outfile.open("bestScore.dat", std::ios::out);
        outfile << score;
        outfile.close();
    }
    g.gameOver();
    return 0;
}