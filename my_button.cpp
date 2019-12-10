#include "my_button.h"

QToolButton *makeButton(const QString &text, QGridLayout &layout, int x, int y, int width, int height){
    // create new Button and set default text and policy
    QToolButton *button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return button;
}
