#include "Number.h"

Number::Number(QWidget *parent)
	: QLabel(parent)
{
	setGeometry(0,0,90,90);
	setValue(0);
	setAlignment(Qt::AlignCenter);
	show();
}

Number::Number(QWidget *parent,int x,int y, int width, int height, int value)
	: QLabel(parent)
{
	qDebug() << x << y << width << height << value;
	setGeometry(x,y,width,height);
	setValue(value);
	setAlignment(Qt::AlignCenter);
	show();
}

Number::~Number()
{

}

void Number::setValue(const int value1)
{
	value = value1;
	setText("");
	switch (value)
	{
	case 2:
		setStyleSheet(LABEL_2);
		break;
	case 4:
		setStyleSheet(LABEL_4);
		break;
	case 8:
		setStyleSheet(LABEL_8);
		break;
	case 16:
		setStyleSheet(LABEL_16);
		break;
	case 32:
		setStyleSheet(LABEL_32);
		break;
	case 64:
		setStyleSheet(LABEL_64);
		break;
	case 128:
		setStyleSheet(LABEL_128);
		break;
	case 256:
		setStyleSheet(LABEL_256);
		break;
	case 512:
		setStyleSheet(LABEL_512);
		break;
	case 1024:
		setStyleSheet(LABEL_1024);
		break;
	case 2048:
		setStyleSheet(LABEL_2048);
		break;
	case 0:
	default:
		setStyleSheet(LABEL_0);
		value = 0;
		break;
	}
	setText("    " + QString::number(value)+"    ");
}

int Number::getValue()
{
	return value;
}

