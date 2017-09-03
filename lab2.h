#ifndef LAB2_H
#define LAB2_H

#include <QtGui/QMainWindow>
#include "ui_lab2.h"
#include "GlWindow.h"


class Lab2 : public QMainWindow
{
	Q_OBJECT

public:
	Lab2(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Lab2();

public slots:
	void randObject();


signals:
	void makeObject(); ///< send signal to make an Object

private:
	Ui::Lab2Class ui;
};

#endif // LAB2_H
