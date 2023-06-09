#pragma once

#include <QObject>
#include <QLabel>

#define LABEL_0 "QLabel{font: normal bold 50px;color:#cbc1b4;background-color:#cbc1b4;}"
#define LABEL_2 "QLabel{font: normal bold 50px;color:#776e65;background-color:#eee4da;}"
#define LABEL_4 "QLabel{font: normal bold 50px;color:#776e65;background-color:#ede0c8;}"
#define LABEL_8 "QLabel{font: normal bold 50px;color:#f9f6f2;background-color:#f2b179;}"
#define LABEL_16 "QLabel{font: normal bold 45px;color:#f9f6f2;background-color:#f59563;}"
#define LABEL_32 "QLabel{font: normal bold 45px;color:#f9f6f2;background-color:#f67c5f;}"
#define LABEL_64 "QLabel{font: normal bold 45px;color:#f9f6f2;background-color:#f65e3b;}"
#define LABEL_128 "QLabel{font: normal bold 35px;color:#f9f6f2;background-color:#edcf72;}"
#define LABEL_256 "QLabel{font: normal bold 35px;color:#f9f6f2;background-color:#edcc61;}"
#define LABEL_512 "QLabel{font: normal bold 35px;color:#f9f6f2;background-color:#edc850;}"
#define LABEL_1024 "QLabel{font: normal bold 30px;color:#f9f6f2;background-color:#edc53f;}"
#define LABEL_2048 "QLabel{font: normal bold 30px;color:#f9f6f2;background-color:#edc22e;}"

class Number  : public QLabel
{
	Q_OBJECT
private:
	int value=0;
public:
	Number(QWidget *parent);
	~Number();
	void setValue(const int value);
	int getValue();
};
