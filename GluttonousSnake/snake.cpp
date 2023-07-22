#include "snake.h"
#include <cstdlib>
#include <ctime>

Snake::Snake(Graph& g): alive(true) {
    food.setFood(g);
    srand((size_t)time(NULL));
    snakeHead = new SnakeNode();                    // 创建蛇头,蛇头位置在合理的且可以容纳一个蛇身的位置
    snakeHead->x = rand() % (Graph::ROW - 3) + 2;
    snakeHead->y = rand() % (Graph::COL - 3) + 2;
    SnakeNode* snakeBody = new SnakeNode();         // 创建一个蛇身,默认蛇身于蛇头的左侧
    snakeBody->next = NULL;
    snakeBody->x = snakeHead->x, snakeBody->y = snakeHead->y - 1;
    snakeHead->next = snakeBody;
    g.setGraph(snakeHead->x, snakeHead->y, Graph::snakeHead);
    g.setGraph(snakeBody->x, snakeBody->y, Graph::snakeBody);
}

Snake::~Snake() {
    while(snakeHead) {
        SnakeNode* it = snakeHead;
        snakeHead = snakeHead->next;
        it->next = NULL;
        delete it;
    }
}

void Snake::addSnakeNode(Graph& g, int x, int y) {
    SnakeNode* cur = new SnakeNode();     // 蛇头移动到新的位置,创建新的蛇头
    cur->x = x, cur->y = y;
    g.setGraph(snakeHead->x, snakeHead->y, Graph::snakeBody);
    cur->next = snakeHead;
    g.setGraph(x, y, Graph::snakeHead);
    snakeHead = cur;
}

void Snake::delSnakeNode(Graph& g) {
    SnakeNode* it = snakeHead;
    if(!it || !(it->next)) return;
    SnakeNode* itn = it->next;
    while (itn->next) {
        it = it->next;
        itn = itn->next;
    }
    g.setGraph(itn->x, itn->y, Graph::emptyArea);
    delete itn;
    itn = NULL;
    it->next = NULL;
}

void Snake::snakeMove(Graph& g, char dir) {
    int x = snakeHead->x, y = snakeHead->y;
    switch (dir) {
        case UP:
            x --;
            break;
        case DOWN:
            x ++;
            break;
        case LEFT:
            y --;
            break;
        case RIGHT:
            y ++;
            break;
    }
    char ch = g.getChar(x, y);
    if(ch <= '9' && ch >= '0') {    // 蛇头迟到了食物
        g.calScore(ch - '0');
        int score = g.getScore();
        char MID[10] = "Middle";
        char QUI[10] = "Quick";
        if(score >= 100) {          // 根据得分调整速度
            g.setSpeed(QUI);
        }
        else if(score >= 60) {
            g.setSpeed(MID);
        }
        addSnakeNode(g, x, y);
        food.setFood(g);            // 食物被吃掉之后,重新设置食物
    }
    else if(ch == Graph::snakeBody) {   // 蛇头和蛇身相碰
        SnakeNode* it = snakeHead;
        while(it->next) it = it->next;
        if(it->x == x && it->y == y) {  // 若和蛇尾相碰,则不认为咬到了自己的身体
            addSnakeNode(g, x, y);
            delSnakeNode(g);
            g.setGraph(x, y, Graph::snakeHead);
        }
        else {                          // 咬到了自己的身体,结束游戏
            addSnakeNode(g, x, y);
            stopLife();
        }
    }
    else if(ch == Graph::wall) {        // 蛇头和墙相撞,结束游戏
        addSnakeNode(g, x, y);
        delSnakeNode(g);
        stopLife();
    }
    else {                              // 正常移动
        addSnakeNode(g, x, y);
        delSnakeNode(g);
    }
}

bool Snake::isAlive() const {
    return alive;
}

void Snake::stopLife() {
    alive = false;
}