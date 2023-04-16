#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_SIZE 15
#define SQUARE_SIZE 40
#define CHESS_RADIUS 15

int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
int current_player = 1; // 1 for player1, 2 for player2

void draw_board();
void draw_chess(int row, int col, int player);
bool check_win(int player);

int main()
{
    initgraph(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE);
    draw_board();
    int row, col;
    while (true)
    {
        while (!MouseHit()) {} // Wait for mouse event
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            row = msg.y / SQUARE_SIZE;
            col = msg.x / SQUARE_SIZE;
            if (board[row][col] == 0)
            {
                draw_chess(row, col, current_player);
                board[row][col] = current_player;
                if (check_win(current_player))
                {
                    TCHAR msg[50];
                    _stprintf_s(msg, _T("玩家 %d 胜利!"), current_player);

                    settextstyle(30, 0, _T("Consolas"));
                    settextcolor(RED);

                    // 显示游戏结束消息
                    outtextxy(200, 200, msg);
                    

                    
                   
                }
                current_player = current_player == 1 ? 2 : 1;
            }
        }
    }
    return 0;
}

void draw_board()
{
    setbkcolor(RGB(164, 255, 202));
    cleardevice();
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        line(SQUARE_SIZE / 2, SQUARE_SIZE / 2 + i * SQUARE_SIZE,
            SQUARE_SIZE / 2 + (BOARD_SIZE - 1) * SQUARE_SIZE,
            SQUARE_SIZE / 2 + i * SQUARE_SIZE);
        line(SQUARE_SIZE / 2 + i * SQUARE_SIZE, SQUARE_SIZE / 2,
            SQUARE_SIZE / 2 + i * SQUARE_SIZE,
            SQUARE_SIZE / 2 + (BOARD_SIZE - 1) * SQUARE_SIZE);
    }
}

void draw_chess(int row, int col, int player)
{
    setfillcolor(player == 1 ? BLACK : WHITE);
    setcolor(player == 1 ? BLACK : WHITE);
    fillcircle(col * SQUARE_SIZE + SQUARE_SIZE / 2,
        row * SQUARE_SIZE + SQUARE_SIZE / 2, CHESS_RADIUS);
}

bool check_win(int player)
{
    int count = 0;
    // Check horizontally
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        count = 0;
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
    // Check vertically
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        count = 0;
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
    // Check diagonally
    for (int i = 0; i <= BOARD_SIZE - 5; i++)
    {
        for (int j = 0; j <= BOARD_SIZE - 5; j++)
        {
            count = 0;
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
    for (int i = 0; i <= BOARD_SIZE - 5; i++)
    {
        for (int j = 4; j < BOARD_SIZE; j++)
        {
            count = 0;
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