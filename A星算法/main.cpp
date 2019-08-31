#include <iostream>
#include <queue>
#include <list>
#include <cmath>
#include <climits>
#include <windows.h>
using namespace std;


struct position
{
    int x;
    int y;
    int F;
    int G;
    int H;
    int dir = 0;
    position* father;
};
static int wall[20][20] = {{0}};
int open[20][20] = {{0}};
int close[20][20] = {{0}};
bool findPath(position* start,position* finish, vector<int>& dirv)
{
    vector<position*> openlist;
    start->dir = -1;
    start->G = 0;
    start->H = abs(start->x-finish->x) + abs(start->y-finish->y);
    start->F = start->H + start->G;
    openlist.push_back(start);
    open[start->x][start->y] = 1;
    while(openlist.size())
    {
        int MinF = INT_MAX;
        position* MinFOfPosition = openlist[0];
        int index = 0;
        position offset[4];
    offset[0].x = 1; offset[0].y = 0;    //→ 0
    offset[1].x = 0; offset[1].y = 1;    //↓ 1
    offset[2].x = -1; offset[2].y = 0;   //← 2
    offset[3].x = 0; offset[3].y = -1;   //↑ 3
        for(int i = 0; i < openlist.size(); i++)
        {
            if(MinF >= openlist[i]->F)
            {
                MinF = openlist[i]->F;
                MinFOfPosition = openlist[i];
                index = i;
            }
        }
        open[MinFOfPosition->x][MinFOfPosition->y] = 0;
        close[MinFOfPosition->x][MinFOfPosition->y] = 1;
        openlist.erase(openlist.begin()+index);
        for(int j = 0; j < 4; j++)
        {
            position* next = new position;                           //MinFOfPosition的附近位置；
            next->x = MinFOfPosition->x + offset[j].x;
            next->y = MinFOfPosition->y + offset[j].y;
            if(wall[next->x][next->y] == 1 || close[next->x][next->y] == 1)
                continue;
            if(wall[next->x][next->y] == 0)
            {
                next->G = MinFOfPosition->G + 1;
                next->H = abs(next->x-finish->x) + abs(next->y-finish->y);
                next->F = next->G + next->H;
                next->father = MinFOfPosition;
                next->dir = j;
                if(openlist.size())
                {
                for(int k = 0; k < openlist.size(); k++)
                {
                    if(next->x == openlist[k]->x && next->y == openlist[k]->y)
                    {
                        if(next->G >= openlist[k]->G)
                            continue;
                    }
                }
                }
                if(next->x == finish->x && next->y == finish->y)
                {
                    finish->x = next->x;
                    finish->y = next->y;
                    finish->G = next->G;
                    finish->H = next->H;
                    finish->F = next->F;
                    finish->dir = next->dir;
                    finish->father = next->father;
                    break;
                }
                openlist.push_back(next);
                open[next->x][next->y] = 1;
            }

        }
        if(finish->dir > 0)
        {
            cout << finish->dir << endl;
            break;
        }
        if(openlist.size() == 0)
            return false;
    }
    position* p = finish;
    while(p != start)
    {
        dirv.push_back(p->dir);
        p = p->father;
    }
    return true;
}



void Pos(int x,int y)  //设置光标位置
{
    COORD pos;
    HANDLE hOutput;
    pos.X = 2*x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}


int main()
{
    for(int i = 0; i < 10; i++)
    {
        wall[i][0] = 1;
        wall[0][i] = 1;
        wall[i][9] = 1;
        wall[9][i] = 1;
    }
    wall[2][2] = 1;
    wall[5][5] = 1;
    wall[2][4] = 1;
    wall[3][4] = 1;
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(wall[i][j])
            {
                Pos(i,j);
                cout << "■";
            }
            else
            {
                Pos(i,j);
                cout << " ";
            }
        }
    }
    position* s = new position;
    position* f = new position;
    vector<int> v;
    s->x = 2;
    s->y = 1;
    f->x = 2;
    f->y = 5;
    findPath(s,f,v);
    for(int i = v.size()-1; i >= 0; i--)
        cout << v[i] << endl;
    cout << "Hello world!" << endl;
    return 0;
}
