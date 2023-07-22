#ifndef _Snake_
#define _Snake_

#include "graph.h"
#include "food.h"

class Snake {
    public:
        enum directions {   // 运行方向
            UP = 'W',
            DOWN = 'S',
            LEFT = 'A',
            RIGHT = 'D'
        };

        struct SnakeNode {  // 蛇可以看成一个单链表,每个蛇结点由定位坐标和下一个蛇结点的指针域构成
            int x;
            int y;
            SnakeNode* next;
        };

        Snake(Graph&);
        ~Snake();

        void addSnakeNode(Graph&, int, int);    // 蛇移动,蛇头为下一个移动到的位置,原来的蛇头变为蛇身
        void delSnakeNode(Graph&);              // 在蛇没有迟到食物的条件下,蛇身不会变长,则蛇的身体可以视为向前移动一步,则原来蛇尾的位置应该做消失处理
        void snakeMove(Graph&, char);           // 蛇的移动
        bool isAlive() const;                   // 是否存活
        void stopLife();                        // 结束游戏
       
    private:
        bool alive;                             // 蛇的存活状态
        SnakeNode* snakeHead;                   // 蛇头指针
        Food food;                              // 用于食物生成
};

#endif // _Snake_