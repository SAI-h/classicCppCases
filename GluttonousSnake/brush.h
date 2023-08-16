#ifndef _Brush_
#define _Brush_

class Brush {   //画刷,绘图工具类
    public:
        void printf_normal(const char);
        void printf_normal(const char*);
        void printf_red(const char);
        void printf_red(const char*);
        void printf_green(const char);
        void printf_green(const char*);
        void printf_yellow(const char);
        void printf_yellow(const char*);
        void printf_blue(const char);
        void printf_blue(const char*);
        void printf_pink(const char);
        void printf_pink(const char*);
        void printf_cyan(const char);
        void printf_cyan(const char*);

        void printf_pink(const bool, const int);    // 第一个参数仅为了区分传参为int还是char,在实现上无实际作用
};

#endif // _Brush_