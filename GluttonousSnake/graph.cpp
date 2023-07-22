#include "graph.h"
#include <string.h>

Graph::Graph(int bestScore):bestScore(bestScore), score(0), speed("Slow") {
    // 建立仅含有墙的空图
    for(int i = 0; i < ROW; i ++)
        for(int j = 0; j < COL; j ++) {
            if(i == 0 || j == 0 || i == ROW - 1 || j == COL - 1) {
                drawGra[i][j] = wall;
            }
            else {
                drawGra[i][j] = emptyArea;
            }
        }
}

void Graph::graphShow() {
    for(int i = 0; i < ROW; i ++) {
        for(int j = 0; j < COL; j ++) {
            if(drawGra[i][j] == snakeBody) {
                if(i % 2) brush.printf_cyan((char)drawGra[i][j]);
                else brush.printf_blue((char)drawGra[i][j]);
            }
            else {
                brush.printf_normal((char)drawGra[i][j]);
            }
            brush.printf_normal(emptyArea);
        }
        if(i == 4) {
            brush.printf_red("\tGLUTTONOUS SNAKE Version.1.0");
        }
        else if(i == 6) {
            brush.printf_yellow("\tSpeed: ");
            brush.printf_yellow(speed);
        }
        else if(i == 8) {
            brush.printf_pink("\tScore: ");
            brush.printf_pink(true, score);
            if(score > bestScore) {
                brush.printf_yellow(" (Good! A new record has been set!)");
            }
        }
        else if(i == 10) {
            brush.printf_pink("\tBest Score: ");
            brush.printf_pink(true, bestScore);
        }
        else if(i == 12) {
            brush.printf_green("\tKey prompt:");
        }
        else if(i == 14) {
            brush.printf_green("\t   Up:W  Down:S  Left:A  Right:D");
        }
        brush.printf_normal("\n");
    }
}

void Graph::setGraph(int x, int y, char c) {
    drawGra[x][y] = c;
}

char Graph::getChar(int x, int y) const {
    return drawGra[x][y];
}

void Graph::calScore(int sc) {
    score += sc;
}

int Graph::getScore() const {
    return score;
}

void Graph::setSpeed(char* SpeedChoice) {
    strcpy(speed, SpeedChoice);
}

char* Graph::getSpeed() {
    return speed;
}

void Graph::gameOver() {
    brush.printf_green("_________           _____            ____      ___       ________    ");
    brush.printf_pink(" ______   __      __    _______    _____         \n");

    brush.printf_green("| ______|          / __\\ \\          / __ \\    / _ \\      |  _____|    ");
    brush.printf_pink("|  __  |  \\ \\    / /   |  _____|  | ___ |         \n");

    brush.printf_green("| |  _______      / /___\\ \\        / /  \\ \\  / / \\ \\     |  |____     ");
    brush.printf_pink("| |  | |   \\ \\  / /    |  |____   | |__| |  \n");

    brush.printf_green("| |__|___   |    / ______  \\      / /    \\ \\/ /   \\ \\    |  _____|    ");
    brush.printf_pink("| |__| |    \\ \\/ /     |  _____|  |  ___ |      \n");

    brush.printf_green("|________|__|   /_/      \\__\\    /_/      \\__/     \\_\\   |__-----|    ");
    brush.printf_pink("|______|     \\__/      |__-----|  |_|   \\_\\    \n");
}