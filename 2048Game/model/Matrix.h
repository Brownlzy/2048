#pragma once
#include <QString>
class Matrix
{
private:
    int matrix[4][4];
public:
    Matrix();
    Matrix(const Matrix& ma);
    ~Matrix();
    /*获得位于(x,y)处的方块值(0为空)*/
    int getNumberIn(int x, int y);
    void setNumberIn(int x, int y,const int value);
    /*获得位于x行的方块值(0为空)*/
    int* getLineOnX(int x);
    void setLineOnX(int x,const int* values);
    /*获得位于y行的方块值(0为空)*/
    int* getLineOnY(int y);
    void setLineOnY(int y,const int* values);

    void printToConsole();
    void printToConsole(QString title);
};

