#ifndef _Food_
#define _Food_

#include "graph.h"

class Food {
    public:
        void setFood(Graph&);   // 在地图上的合适区域随机放置食物

    private:
        int x;
        int y;
        int score;
};

#endif // _Food_