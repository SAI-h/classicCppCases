#ifndef _Tool_
#define _Tool_
#include <unordered_map>
// 输出错误信息
void error_handling(char* msg);
// 初始化用户信息
void init_isExist( std::unordered_map<std::string, std::string>& utop );
#endif // _Tool_