#pragma once
class Matrix
{
private:
    int matrix[4][4];
public:
    /*���λ��(x,y)���ķ���ֵ(0Ϊ��)*/
    int getNumberIn(int x, int y);
    /*���λ��x�еķ���ֵ(0Ϊ��)*/
    int* getLineOnX(int x);
    /*���λ��y�еķ���ֵ(0Ϊ��)*/
    int* getLineOnY(int y);
};

