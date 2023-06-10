#include "Move.h"

OperateList Move::move(Direction direction,Matrix *matrix,int *score)
{
    OperateList oplist;
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
                    oplist.addOperate(new MergeTo(j, no, k, no, i, no, temp));
                }
                else if(j < 4)
                {
                    int temp = ano[j];
                    ano[j] = 0;
                    ano[i] = temp;
                    oplist.addOperate(new MoveTo(j, no, i, no, temp));
                }
            }
            ano;
            matrix->setLineOn(direction,no, ano);
        }
    return oplist;
}
