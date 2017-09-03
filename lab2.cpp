#include "lab2.h"

Lab2::Lab2(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	connect(ui.ObjectButton, SIGNAL(clicked()), this, SLOT(randObject()));
}

Lab2::~Lab2()
{}
void Lab2::randObject()
{
	makeObject();
}