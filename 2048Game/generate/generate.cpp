#include "generate.h"


void gen::addNewNumber() {
    srand(time(0));
    while (true) {
        int i = rand() % SIZE; // 在0~3之间随机选一个数
        int j = rand() % SIZE; // 在0~3之间随机选一个数
        if (ma[i][j] == 0) { // 如果这个位置是空的
            int num = rand() % 2 == 0 ? 2 : 4; // 生成2或4
            ma[i][j] = num; // 将新生成的2或4放到(i,j)的位置上
            break;
        }
    }
}