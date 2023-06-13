#include "gui/GameWindow.h"
#include <QtWidgets/QApplication>
#include "controller/MainControl.h"
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GameWindow w;
	MainControl mc(&w);
	w.show();
	return a.exec();
}
