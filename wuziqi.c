#include <graphics.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <stdio.h> 

#define BOARD_SIZE 15 // 棋盘大小为15x15
#define SQUARE_SIZE 40 // 格子大小为40x40
#define CHESS_RADIUS 15 // 棋子半径为15

//棋盘和玩家初始化
int board[BOARD_SIZE][BOARD_SIZE] = {0}; // 初始化棋盘为全0
int current_player = 1; // 当前玩家编号，初始为1

//绘制棋盘和棋子
void draw_board(); 
void draw_chess(int row, int col, int player); 
bool check_win(int player); 

int main(){

    // 初始化图形界面
    initgraph(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE); 
    draw_board(); 
    int row, col; 

    //进行游戏
    while (true) 
    {
        while (!MouseHit()) // 如果鼠标没有点击，则等待
        {
            // 等待鼠标事件
        } 

        
        MOUSEMSG msg = GetMouseMsg(); // 获取鼠标动作
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            row = msg.y / SQUARE_SIZE; 
            col = msg.x / SQUARE_SIZE; 

            // 如果该格子没有落子和有骡子的情况
            if (board[row][col] == 0) 
            {
                draw_chess(row, col, current_player); 
                board[row][col] = current_player; // 在棋盘上记录该位置有该玩家的棋子

                 // 如果该玩家胜利
                if (check_win(current_player))
                {
                    TCHAR msg[50]; 
                    _stprintf_s(msg, _T("玩家 %d 胜利!"), current_player); // 将提示信息格式化为字符串
                    settextstyle(30, 0, _T("Consolas")); 
                    settextcolor(WHITE); 

                    // 显示游戏结束消息
                    outtextxy(200, 200, msg);
                }
                current_player = current_player == 1 ? 2 : 1; // 切换当前玩家
            }
        }
    }
    return 0; 
}

void draw_board(){
    setbkcolor(RGB(153, 51, 0)); // 设置背景颜色
    cleardevice(); // 清除画布

    //绘制线条
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        //横线
        line(SQUARE_SIZE / 2, SQUARE_SIZE / 2 + i * SQUARE_SIZE,SQUARE_SIZE / 2 + (BOARD_SIZE - 1) * SQUARE_SIZE,SQUARE_SIZE / 2 + i * SQUARE_SIZE);
        //竖线
        line(SQUARE_SIZE / 2 + i * SQUARE_SIZE, SQUARE_SIZE / 2,SQUARE_SIZE / 2 + i * SQUARE_SIZE,SQUARE_SIZE / 2 + (BOARD_SIZE - 1) * SQUARE_SIZE);
    }
}

//绘制棋子
void draw_chess(int row, int col, int player)
{

    //根据玩家不同，绘制不同棋子
    setfillcolor(player == 1 ? BLACK : WHITE);
    setcolor(player == 1 ? BLACK : WHITE);
    fillcircle(col * SQUARE_SIZE + SQUARE_SIZE / 2,row * SQUARE_SIZE + SQUARE_SIZE / 2, CHESS_RADIUS);
}

//检测游戏情况
bool check_win(int player)
{
    int count = 0;

    //情况1：横着五子连一线
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        count = 0;//换行计数清零
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == player)
            {
                count++;
                if (count == 5)
                    return true;
            }
            else
            {
                count = 0;
            }
        }
    }
    
    //情况2：竖着五子连一线
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        count = 0;//换列计数清零
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i][j] == player)
            {
                count++;
                if (count == 5)
                    return true;
            }
            else
            {
                count = 0;
            }
        }
    }
   
   //情况3：“\”着五子连一线
    for (int i = 0; i <= BOARD_SIZE - 5; i++)
    {
        for (int j = 0; j <= BOARD_SIZE - 5; j++)
        {
            count = 0;//换格子计数器清零
            for (int k = 0; k < 5; k++)
            {
                if (board[i + k][j + k] == player)
                {
                    count++;
                    if (count == 5)
                        return true;
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

 //情况4：“/”着五子连一线
    for (int i = 0; i <= BOARD_SIZE - 5; i++)
    {
        for (int j = 4; j < BOARD_SIZE; j++)
        {
            count = 0;//换格子计数器清零
            for (int k = 0; k < 5; k++)
            {
                if (board[i + k][j - k] == player)
                {
                    count++;
                    if (count == 5)
                        return true;
                }
                else
                {
                    count = 0;
                }
            }
        }
    }
    return false;
}