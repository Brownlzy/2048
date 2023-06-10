#include "generate.h"

generate::generate() {
}

void generate::addNewNumber(Matrix* m) {

    srand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));
  
    int i = 0, j = 0;
    //找空格数
    struct Ns n[15];
    int ni = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (m->getNumberIn(i,j) == 0) {
                n[ni].i = i;
                n[ni].j = j;
                ni++;
            }
        }
    }

    //判断游戏是否结束
    if (ni == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                if (m->getNumberIn(i, j) == m->getNumberIn(i, j+1)) {
                    return;
                }
            }
        }
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 3; i++) {
                if (m->getNumberIn(i, j) == m->getNumberIn(i+1,j)) {
                    return;
                }
            }
        }
        qDebug() << "矩阵已满";
     
        return;
    }
    int randx = rand() % ni;
    m->setNumberIn(n[randx].i, n[randx].j,2);
 
}