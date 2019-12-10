#include "mybutton.h"

#include <QToolButton>

MyButton::MyButton(const QString &text, int x, int y, int height, int width){
    // create new Button and set default text and policy
    button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QToolButton* MyButton::getButton()
{
    return button;
}

MyButton::~MyButton()
{
    delete(button);
}
