#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QApplication>
#include <QGridLayout>
#include <QToolButton>

QToolButton *makeButton(const QString &text, QGridLayout &layout, int x, int y, int width, int height);

#endif // MY_BUTTON_H
