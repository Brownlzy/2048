#include "generate.h"


void gen::addNewNumber() {
    srand(time(0));
    while (true) {
        int i = rand() % SIZE; // ��0~3֮�����ѡһ����
        int j = rand() % SIZE; // ��0~3֮�����ѡһ����
        if (ma[i][j] == 0) { // ������λ���ǿյ�
            int num = rand() % 2 == 0 ? 2 : 4; // ����2��4
            ma[i][j] = num; // �������ɵ�2��4�ŵ�(i,j)��λ����
            break;
        }
    }
}