#pragma once
class Matrix
{
private:
    int matrix[4][4];
public:
    /*获得位于(x,y)处的方块值(0为空)*/
    int getNumberIn(int x, int y);
    /*获得位于x行的方块值(0为空)*/
    int* getLineOnX(int x);
    /*获得位于y行的方块值(0为空)*/
    int* getLineOnY(int y);
};

