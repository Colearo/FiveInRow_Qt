#ifndef FIR_H
#define FIR_H
#include <iostream>
#include <vector>
using namespace std;
#define AION false

class POINT//一个坐标类
{
public:
    int x;
    int y;
    POINT(const int X=-1, const int Y=-1)
        {x = X; y = Y;}
};
class FIR
{
public:
    FIR();
    ~FIR(){}
    void Judge(int &Who);//判断函数，判断胜负
    bool Process(int x,int y,int &Who);//处理落子的坐标点
    void Clear();//清理棋盘数据
    bool Backto();//悔棋
    int data[20][20];//棋盘的落子数据，0为没有，1为黑棋，2为白棋
    bool AIon;//AI
private:
    int total;//棋盘的落子总数
    std::vector <POINT> last;//将棋盘的落子先后顺序存入vector中，在悔棋函数中使用
    void SetScore(const int i, const int j, const int Who,
                      vector<vector<int> > & State); //评分函数
    int p_Score(int num, int bp[]); //实际的评分函数
    void Way(POINT & ps);//生成棋子
};

#endif // FIR_H
