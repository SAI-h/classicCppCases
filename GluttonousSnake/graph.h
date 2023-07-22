#ifndef _Graph_
#define _Graph_

#include "brush.h"

class Graph {
    public:
        enum Symbol {   // 绘图标记
            wall = '#',
            emptyArea = ' ',
            snakeHead = '@',
            snakeBody = '='
        };

        enum Speed {    // 蛇的运行速度,刷新时间越短,速度越快
            SLOW = 200,
            MIDDLE = 100,
            QUICK = 60,
        };

        enum dimension { // 界面尺寸(行高x列高)
            ROW = 25,
            COL = 30
        };

        Graph(int);
        void graphShow();                   // 绘图
        void setGraph(int, int, char);      // 更新图, 蛇移动觅食过程中需要对绘图的二维数组进行更新
        char getChar(int, int) const;       // 获取绘图数组中对应位置上的字符
        void calScore(int);                 // 计算当前的得分
        int getScore() const;               // 获取当前的得分
        void setSpeed(char*);               // 设置速度
        char* getSpeed();                   // 获取速度
        void gameOver();                    // 游戏结束字样输出

    private:
        char drawGra[ROW][COL];             // 绘图数组
        Brush brush;                        // 工具画刷
        char speed[10];                     // 速度
        int score;                          // 得分
        int bestScore;                      // 历史最佳得分
};

#endif // _Graph_