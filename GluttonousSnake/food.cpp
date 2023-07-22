#include "food.h"
#include "graph.h"
#include <cstdlib>
#include <ctime>

void Food::setFood(Graph& g) {
    srand((size_t)time(NULL));
    score = rand() % 9 + 1; // 设置获取到的每个食物得分(1~9)
    do {
        x = rand() % (Graph::ROW - 2) + 1;
        y = rand() % (Graph::COL - 2) + 1;
    } while(g.getChar(x, y) != Graph::emptyArea); // 保证食物的设置不出现在墙,也不出现在蛇身体出现到的地方
    g.setGraph(x, y, '0' + score);
}