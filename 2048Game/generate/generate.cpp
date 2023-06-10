#include "generate.h"

generate::generate() {
    widget = new QWidget();//??
}

void generate::addNewNumber() {
    srand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));
    srand(time(0));
    int i = 0, j = 0;
    struct Ns n[15];
    int ni = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (ma[i][j] == 0) {
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
                if (ma[i][j] == ma[i][j + 1]) {
                    return;
                }
            }
        }
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 3; i++) {
                if (ma[i][j] == ma[i + 1][j]) {
                    return;
                }
            }
        }
        QMessageBox::about(widget, "游戏失败", "分数为：" + QString::number(score) + " ");
        return;
    }
    int rand = rand() % ni;
    ma[n[rand].i][n[rand].j] = 2;

    //while (true) {

    //    int i = rand() % SIZE; // 在0~3之间随机选一个数
    //    int j = rand() % SIZE; // 在0~3之间随机选一个数
    //    if (ma[i][j] == 0) { // 如果这个位置是空的
    //        int num = rand() % 2 == 0 ? 2 : 4; // 生成2或4
    //        ma[i][j] = num; // 将新生成的2或4放到(i,j)的位置上
    //        break;
    //    }
    //}
}