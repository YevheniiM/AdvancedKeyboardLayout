#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QString>
#include <QToolButton>



class MyButton
{
public:
    QToolButton *button;
    MyButton(const QString &text, int x, int y, int height, int width);
    QToolButton* getButton();
    ~MyButton();
};

#endif // MYBUTTON_H
