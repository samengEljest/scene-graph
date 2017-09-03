#include <QtGui/QApplication>
#include "GlWindow.h"
#include "lab2.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GlWindow w;
	Lab2 w2;
	QObject::connect(&w2, SIGNAL(makeObject()) , &w, SLOT(RandObject()));
	w.show();
	w2.show(); 
	return a.exec();
}