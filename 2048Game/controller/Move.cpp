#include "Move.h"

OperateList* Move::move(Direction direction,Matrix *matrix,int *score,bool *isNew)
{
    *isNew=false;
    OperateList* oplist=new OperateList();
        for (int no = 0; no < 4; no++) 
        {
            int* ano = matrix->getLineOn(direction,no);
            for (int i = 0; i < 4; i++) {
                int j, k;
                for (j = i; j < 4; j++) {
                    if (ano[j] != 0)
                        break;
                }
                for (k = j+1; k < 4; k++) {
                    if (ano[k] != 0)
                        break;
                }
                if (j<4&&k<4&&ano[j] == ano[k]) {
                    int temp= ano[j] * 2;
                    ano[j] = 0;
                    ano[k] = 0;
                    ano[i] = temp;
                    *score += temp;
                    switch (direction)
                    {
                    case UP:
                        oplist->addOperate(new MergeTo( j,no,  k,no,  i,no, temp));
                        *isNew = true;
                        break;
                    case LEFT:
                        oplist->addOperate(new MergeTo(no, j, no,k,  no, i, temp));
                        *isNew = true;
                        break;
                    case RIGHT:
                        oplist->addOperate(new MergeTo( no,3-j, no,3-k,  no,3-i,  temp));
                        *isNew = true;
                        break;
                    case DOWN:
                        oplist->addOperate(new MergeTo(3-j,no, 3-k, no,  3- i,no, temp));
                        *isNew = true;
                        break;
                    default:
                        break;
                    }
                }
                else if(j < 4)
                {
                    int temp = ano[j];
                    ano[j] = 0;
                    ano[i] = temp;
                    switch (direction)
                    {
                    case UP:
                    oplist->addOperate(new MoveTo( j,no, i,no,  temp));
                    if (j!=i)
                    *isNew = true;
                        break;
                    case LEFT:
                    oplist->addOperate(new MoveTo( no,j, no,i,  temp));
                    if (j != i)
                    *isNew = true;
                        break;
                    case DOWN:
                    oplist->addOperate(new MoveTo( 3-j,no, 3-i, no, temp));
                    if ((3-j )!= (3-i))
                    *isNew = true;
                        break;
                    case RIGHT:
                    oplist->addOperate(new MoveTo( no,3-j,  no,3-i, temp));
                    if ((3 - j) != (3 - i))
                    *isNew = true;
                        break;
                    default:
                        break;
                    }
                }
            }
            ano;
            matrix->setLineOn(direction,no, ano);
        }
    return oplist;
}
