#include "fir.h"

FIR::FIR()//五子棋类的构造函数
{
   memset(data, 0, 20 * 20 * sizeof(int));
   total=0;
   AIon = AION;
}
void FIR::Judge(int &Who)//判断函数，判断胜负
{
    int N=20;//棋盘宽度
    int state = 0;
    //int x=last[total-1].x,y=last[total-1].y;//获取最后一个落子的点坐标
    for(int sum = total-1; sum >= 0 ; sum--)
    {
    //for (int x = 0; x < N; x++)
    //{
    //   for (int y = 0; y < N; y++)
    //  {
        int x=last[sum].x,y=last[sum].y;//获得棋盘棋子数据
        for (int i = 0; i < 4; i++)
        {
            int k, j;
            switch (i)
            {
            case 0: //横向
                k = x+1;//从左向右检测
                while (k < N && data[k][y] == data[x][y])
                {
                    state++;
                    k++;
                }
                if (state >= 4)
                {
                    Who = data[x][y];
                    return;
                }
                else
                {
                    state = 0;
                }
                break;
            case 1: //竖向
                j = y + 1; //从上往下
                while (j < N && data[x][j] == data[x][y])
                {
                    state++;
                    j++;
                }
                if (state >= 4)
                {
                    Who = data[x][y];
                    return;
                }
                else
                {
                    state = 0;
                }
                break;
            case 2: //左上到右下
                k = x + 1;
                j = y + 1;
                while (k < N && j < N && data[k][j] == data[x][y])
                {
                    state++;
                    k++;
                    j++;
                }
                if (state >= 4)
                {
                    Who = data[x][y];
                    return;
                }
                else
                {
                    state = 0;
                }
                break;
            case 3: //右上到左下
                k = x - 1;
                j = y + 1;
                while (k >= 0 && j < N && data[k][j] == data[x][y])
                {
                    state++;
                    k--;
                    j++;
                }
                if (state >= 4)
                {
                    Who = data[x][y];
                    return;
                }
                else
                {
                    state = 0;
                }
                break;
            default:
                break;
             }

          }
       }
    Who=0;
    return;
}

bool FIR::Process(int X,int Y,int &Who) //处理落子的坐标点
{
    if(X >= 20 && X < 420 && Y >= 20 && Y < 420)
    {
        int x = (X - 10) / 20;//鼠标转化的坐标点为棋盘的坐标
        int y = (Y - 10) / 20;
        if (!data[x][y])
        {
            POINT temp(x,y);
            data[x][y] = total++% 2 + 1;
            last.push_back(temp);
            if(AIon==true)
            {
                Way(temp);
                data[temp.x][temp.y] = total++% 2 + 1;
                last.push_back(temp);
            }
            Judge(Who);
        }
        return true;
    }
    return false;
}

void FIR::Clear()   //清理棋盘数据
{
    int i,j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            data[i][j]=0;
        }
     }
    total=0;
    last.clear();
}
bool FIR::Backto()//悔棋
{
    total--;
    if(total<0){
        return false;
    }
    data[last[total].x][last[total].y]=0;
    last.pop_back();
    return true;
}

void FIR::SetScore(const int i, const int j, const int Who,
                    vector<vector<int> > & State)
{
    const int N = 20;
    int Another; //与要求的状态相对的另一方
    if (Who == 1)
    {
        Another = 2;
    }
    else if (Who == 2)
    {
        Another = 1;
    }
    else
    {
        return;
    }
    int bp[2], k, num, max = 0, temp = 0;

    //横向
    //向右
    bp[0] = 1; bp[1] = 1;
    num = 0;
    for (k = 1; k < N - i; k++)
    {
        if (data[i+k][j] == Who)
        {
            num++;
            continue;
        }
        if (data[i+k][j] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (data[i+k][j] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //向左
    for (k = 1; k <= i; k++)
    {
        if (data[i-k][j] == Who)
        {
            num++;
            continue;
        }
        if (data[i-k][j] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (data[i-k][j] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    //调用评分函数
    temp = p_Score(num, bp);
    max += temp;

    //纵向
    bp[0] = 1; bp[1] = 1;
    num = 0;
    //向下
    for (k = 1; k < N - j; k++)
    {
        if (data[i][j+k] == Who)
        {
            num++;
            continue;
        }
        if (data[i][j+k] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (data[i][j+k] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //向上
    for (k = 1; k <= j; k++)
    {
        if (data[i][j-k] == Who)
        {
            num++;
            continue;
        }
        if (data[i][j-k] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (data[i][j-k] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    //从左上到右下
    bp[0] = 1; bp[1] = 1;
    num = 0;

    //下
    for (k = 1; k < N-i && k < N-j; k++)
    {
        if (data[i+k][j+k] == Who)
        {
            num++;
            continue;
        }
        if (data[i+k][j+k] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (data[i+k][j+k] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //上
    for (k = 1; k <= j && k <= i; k++)
    {
        if (data[i-k][j-k] == Who)
        {
            num++;
            continue;
        }
        if (data[i-k][j-k] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (data[i-k][j-k] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    //从右上到左下
    bp[0] = 1; bp[1] = 1;
    num = 0;
    //下
    for (k = 1; k < N-j && k <= i; k++)
    {
        if (data[i-k][j+k] == Who)
        {
            num++;
            continue;
        }
        if (data[i-k][j+k] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (data[i-k][j+k] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //上
    for (k = 1; k <= j && k < N-i; k++)
    {
        if (data[i+k][j-k] == Who)
        {
            num++;
            continue;
        }
        if (data[i+k][j-k] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (data[i+k][j-k] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    if (max > State[i][j])
    {
        State[i][j] = max;
    }
}

//实际的评分函数
int FIR::p_Score(int num, int bp[])
{
    int max = 0;
    if (num >= 4)
    {
        max += 10000; //成五
    }
    else if (num == 3)
    {
        if (bp[1] == 1 && bp[0] == 1) //不成五
        {
            max += 0;
        }
        else if (bp[1] == 0 && bp[0] == 0) //活四
        {
            max += 3000;
        }
        else
        {
            max += 900; //冲四
        }
    }
    else if (num == 2)
    {
        if (bp[0] == 0 && bp[1] == 0)
        {
            max += 460; //活三
        }
        else if (bp[0] == 1 && bp[1] == 1)
        {
            max += 0; //不成五
        }
        else
        {
            max += 30; //死三
        }
    }
    else if (num == 1)
    {
        if (bp[0] == 0 && bp[1] == 0)
        {
            max += 45;  //活二
        }
        else if (bp[0] == 1 && bp[1] == 1)
        {
            max += 0;
        }
        else
        {
            max += 5;
        }
    }
    else if (num == 0)
    {
        if (bp[0] == 0 && bp[1] == 0)
        {
            max += 3;
        }
        else if (bp[0] == 1 && bp[1] == 1)
        {
            max += 0;
        }
        else
        {
            max += 1;
        }
    }
    return max;
}
//算法3：随机算法，随机从棋盘上还空着的格子里选出ChooseN个（如果剩余格子小于ChooseN则全选），
//评分，分值最高的就是算法选择的落子点
void FIR::Way(POINT & ps)
{
    const int ChooseN = 300;
    //决定随机选取的格子数
    const int N=20;
    int n;
    if (N*N - total <= ChooseN)
    {
        n = N*N - total;
    }
    else
    {
        n = ChooseN;
    }

    srand(time(NULL));
    vector<POINT> Choose(2*n);  //候选的点的数组
    vector<int> Value(2*n);    //评估的值的数组

    //初始化计算机和人的状态矩阵
    vector<vector<int> > HumanState, ComputerState;
    vector<int> temp(N, 0);
    for (int i = 0; i < N; i++)
    {
        HumanState.push_back(temp);
        ComputerState.push_back(temp);
    }

    for (int i = 0; i < n; i++)
    {
        POINT tempPs;
        //随机找到一个没有棋子的点
        do
        {
            tempPs.x = rand()%N;
            tempPs.y = rand()%N;
        }while (data[tempPs.x][tempPs.y] != 0);
        SetScore(tempPs.x, tempPs.y, 1, HumanState);
        SetScore(tempPs.x, tempPs.y, 2, ComputerState);
        //人的
        Choose[i].x = tempPs.x;
        Choose[i].y = tempPs.y;
        Value[i] = HumanState[tempPs.x][tempPs.y];
        //计算机的
        Choose[i+ChooseN].x = tempPs.x;
        Choose[i+ChooseN].y = tempPs.y;
        Value[i+ChooseN] = HumanState[tempPs.x][tempPs.y];
    }

    int MaxP = 0, MaxC = 0;
    for (int i = 0; i < ChooseN; i++)
    {
        if (Value[i] > MaxP)
        {
            MaxP = i;
        }
        if (Value[i+ChooseN] > MaxC)
        {
            MaxC = i+ChooseN;
        }
    }
    if (Value[MaxP] >= Value[MaxC])
    {
        ps.x = Choose[MaxP].x;
        ps.y = Choose[MaxP].y;
    }
    else
    {
        ps.x = Choose[MaxC].x;
        ps.y = Choose[MaxC].y;
    }
}

