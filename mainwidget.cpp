#include <math.h>
#include "my_button.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QCheckBox>
#include "mainwidget.h"
#include <iostream>
#include "json_manager.h"
#ifdef __linux__
#include <signal.h>
#elif _WIN32
    // windows code goes here
#else

#endif

MainWidget::MainWidget() {
    // create two areas, where program will take out results
    display_old_layout = new QLineEdit("New keyboard layout input");
    display_old_layout->setReadOnly(true);
    display_old_layout->setAlignment(Qt::AlignRight);
    QFont font = display_old_layout->font();
    font.setPointSize(font.pointSize() + 10);
    display_old_layout->setFont(font);

    display_new_layout = new QLineEdit("Old keyboard layout input");
    display_new_layout->setReadOnly(true);
    display_new_layout->setAlignment(Qt::AlignRight);
    display_new_layout->setFont(font);

    // create new grid layout
    layout = new QGridLayout();
    layout->addWidget(display_old_layout, 0, 0, 1, 20);
    layout->addWidget(display_new_layout, 1, 0, 1, 20);


    make_button("esc", 2, 0, 1, 1);
    for(int i = 1; i <= 12; ++i){
        make_button( "f" + QString::number(i), 2, i, 1, 1);
    }
    make_button( "pause\nbreak", 2, 13, 1, 1);
    make_button( "prt sc\nsysrq", 2, 14, 1, 1);
    make_button( "delete\ninsert", 2, 15, 1, 1);
    make_button( "home", 2, 16, 1, 1);
    make_button( "pgup", 2, 17, 1, 1);
    make_button( "pgdn", 2, 18, 1, 1);
    make_button( "end", 2, 19, 1, 1);


    make_button("`", 3, 0, 1, 1);
    for(int i = 1; i <= 10; ++i){
        make_button( QString::number(i % 10), 3, i, 1, 1);
    }
    make_button( "-", 3, 11, 1, 1);
    make_button( "=", 3, 12, 1, 1);
    make_button( "backspace", 3, 13, 1, 3);
    make_button( "num lk\nscr lk", 3, 16, 1, 1);
    make_button( "/", 3, 17, 1, 1);
    make_button( "*", 3, 18, 1, 1);
    make_button( "-", 3, 19, 1, 1);


    make_button("tab", 4, 0, 1, 2);
    make_button("q", 4, 2, 1, 1);
    make_button("w", 4, 3, 1, 1);
    make_button("e", 4, 4, 1, 1);
    make_button("r", 4, 5, 1, 1);
    make_button("t", 4, 6, 1, 1);
    make_button("y", 4, 7, 1, 1);
    make_button("u", 4, 8, 1, 1);
    make_button("i", 4, 9, 1, 1);
    make_button("o", 4, 10, 1, 1);
    make_button("p", 4, 11, 1, 1);
    make_button("[", 4, 12, 1, 1);
    make_button("]", 4, 13, 1, 1);
    make_button("\\", 4, 14, 1, 2);
    make_button("7", 4, 16, 1, 1);
    make_button("8", 4, 17, 1, 1);
    make_button("9", 4, 18, 1, 1);
    make_button("+", 4, 19, 2, 1);


    make_button("caps lock", 5, 0, 1, 2);
    make_button("a", 5, 2, 1, 1);
    make_button("s", 5, 3, 1, 1);
    make_button("d", 5, 4, 1, 1);
    make_button("f", 5, 5, 1, 1);
    make_button("g", 5, 6, 1, 1);
    make_button("h", 5, 7, 1, 1);
    make_button("j", 5, 8, 1, 1);
    make_button("k", 5, 9, 1, 1);
    make_button("l", 5, 10, 1, 1);
    make_button(";", 5, 11, 1, 1);
    make_button("'", 5, 12, 1, 1);
    make_button("enter", 5, 13, 1, 3);
    make_button("4", 5, 16, 1, 1);
    make_button("5", 5, 17, 1, 1);
    make_button("6", 5, 18, 1, 1);


    make_button("shift", 6, 0, 1, 3);
    make_button("z", 6, 3, 1, 1);
    make_button("x", 6, 4, 1, 1);
    make_button("c", 6, 5, 1, 1);
    make_button("v", 6, 6, 1, 1);
    make_button("b", 6, 7, 1, 1);
    make_button("n", 6, 8, 1, 1);
    make_button("m", 6, 9, 1, 1);
    make_button(",", 6, 10, 1, 1);
    make_button(".", 6, 11, 1, 1);
    make_button("/", 6, 12, 1, 1);
    make_button("right shift", 6, 13, 1, 2);
    make_button("up", 6, 15, 1, 1);
    make_button("1", 6, 16, 1, 1);
    make_button("2", 6, 17, 1, 1);
    make_button("3", 6, 18, 1, 1);
    make_button("enter", 6, 19, 2, 1);


    make_button("ctrl", 7, 0, 1, 1);
    make_button("fn", 7, 1, 1, 1);
    make_button("win", 7, 2, 1, 1);
    make_button("alt", 7, 3, 1, 1);
    make_button("space", 7, 4, 1, 6);
    make_button("right alt", 7, 10, 1, 1);
    make_button("context\nmenu", 7, 11, 1, 1);
    make_button("right ctrl", 7, 12, 1, 2);
    make_button("left", 7, 14, 1, 1);
    make_button("down", 7, 15, 1, 1);
    make_button("right", 7, 16, 1, 1);
    make_button("0\ninsert", 7, 17, 1, 1);
    make_button(".\ndelete", 7, 18, 1, 1);

    QToolButton* apply_button = make_system_button("Apply", 8, 17, 1, 3);
    QToolButton* delete_button = make_system_button("Delete", 8, 14, 1, 3);
    checkBox = new QCheckBox(tr("Multiple keys"));
    layout->addWidget(checkBox, 8, 3, 1, 3);
    QObject::connect(apply_button, SIGNAL(clicked()), this, SLOT(apply()));
    QObject::connect(delete_button, SIGNAL(clicked()), this, SLOT(deleteHooks()));

    active_button = make_system_button("Active button", 8, 0, 1, 3);
    clear = true;
    activeButton = "";
    is_key_pressed = false;
    // set layout, name and icon of window
    setLayout(layout);
    setWindowTitle("Smart Keyboard");
    setWindowIcon(QIcon(":/keyboard.png"));

    const std::string name{"/home/popenyuk/AdvancedKeyboardLayout/keyboardlayout.json"};
//    try {
//        remapperConf = confs_from_json(name);
//    } catch (...) {
//    }
//    write_to_json(name, 0, "", 0.5, changed_vector_of_buttons);
}

MainWidget::~MainWidget()
{
    for(auto &button: all_buttons){
        delete(std::get<0>(button.second));
    }
}

QString MainWidget::getRightStringOfButton(const QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Escape:
            return "esc";
        case Qt::Key_Tab:
            return "tab";
        case Qt::Key_CapsLock:
            return "caps lock";
        case Qt::Key_Shift:
            return "shift";
        case Qt::Key_Control:
            return "ctrl";
        case Qt::Key_F1:
            return "f1";
        case Qt::Key_F2:
            return "f2";
        case Qt::Key_F3:
            return "f3";
        case Qt::Key_F4:
            return "f4";
        case Qt::Key_F5:
            return "f5";
        case Qt::Key_F6:
            return "f6";
        case Qt::Key_F7:
            return "f7";
        case Qt::Key_F8:
            return "f8";
        case Qt::Key_F9:
            return "f9";
        case Qt::Key_F10:
            return "f10";
        case Qt::Key_F11:
            return "f11";
        case Qt::Key_F12:
            return "f12";
        case Qt::Key_Pause:
            return "pause\nbreak";
        case Qt::Key_Print:
            return "prt sc\nsysrq";
        case Qt::Key_Delete:
            return "delete\ninsert";
        case Qt::Key_Home:
            return "home";
        case Qt::Key_PageUp:
            return "pgup";
        case Qt::Key_PageDown:
            return "pgdn";
        case Qt::Key_End:
            return "end";
        case Qt::Key_Backspace:
            return "backspace";
        case Qt::Key_NumLock:
            return "num lk\nscr lk";
        case Qt::Key_Enter:
            return "numpadenter";
        case Qt::Key_Return:
            return "enter";
        case Qt::Key_Up:
            return "up";
        case Qt::Key_Down:
            return "down";
        case Qt::Key_Left:
            return "left";
        case Qt::Key_Right:
            return "right";
        case Qt::Key_Alt:
            return "alt";
        case Qt::Key_Space:
            return "space";
    }
}

void MainWidget::make_button(const QString &text, int x, int y, int height, int width){
    // create new Button and set default text and policy
    QToolButton *button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(button, x, y, height, width);
    if(all_buttons.find(text) == all_buttons.end()){
        all_buttons[text] = std::make_tuple(button, x, y);
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(keypressed()));
    }else{
        all_buttons["numpad" + text] = std::make_tuple(button, x, y);
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(keypressed()));
    }
}

QToolButton* MainWidget::make_system_button(const QString &text, int x, int y, int height, int width){
    // create new Button and set default text and policy
    QToolButton *button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(button, x, y, height, width);
    return button;
}

void MainWidget::keypressed(const QString &text)
{
    // e.g. casting to the class you know its connected with
    QToolButton* button = nullptr;
    if(is_key_pressed == 0){
        button = qobject_cast<QToolButton*>(sender());
    }
    QString txt = text;
    if(button != nullptr)
    {
        txt = button->text();
    }
    if(txt != ""){
        if((button == nullptr && activeButton == "")){
            if(clear){
                display_new_layout->setText("");
                display_old_layout->setText("");
                clear = false;
            }
            if(txt == "backspace"){
                if(display_new_layout->text().length() >= 1){
                    display_new_layout->setText(display_new_layout->text().left(display_new_layout->text().length() - 1));
                }
                if(display_old_layout->text().length() >= 1){
                    display_old_layout->setText(display_old_layout->text().left(display_old_layout->text().length() - 1));
                }
            }else if(txt == "space"){
                display_old_layout->setText(display_old_layout->text() + " ");
            }else{
                display_old_layout->setText(display_old_layout->text() + txt);
            }
            activeButton = "";
        }else if(button != nullptr && activeButton == ""){
            activeButton = txt;
            active_button->setText(activeButton);
        }else if(activeButton != ""){
            QToolButton *new_button = std::get<0>(all_buttons.find(activeButton)->second);
            if(!checkBox->checkState()){
                changed_vector_of_buttons[activeButton.toStdString()].clear();
                new_button->setText(txt);
            }
            changed_vector_of_buttons[activeButton.toStdString()].push_back(txt.toStdString());
            activeButton = "";
            active_button->setText("Active button");
        }
    }
    if(is_key_pressed > 0 && button == nullptr && text == ""){
        is_key_pressed -= 1;
    }
}

void MainWidget::apply()
{
    const std::string name{"/home/popenyuk/AdvancedKeyboardLayout/keyboardlayout.json"};
    auto current_json = confs_from_json(name);
    if(checkBox->checkState()){
        write_to_json(name, current_json.remapper_pid, "long_press", 0.5, changed_vector_of_buttons);
    }else{
        write_to_json(name, current_json.remapper_pid, "one_press", 0, changed_vector_of_buttons);
    }
#ifdef __linux__
    kill(current_json.remapper_pid, SIGUSR1);
#elif _WIN32
    // windows code goes here
#else

#endif
}

void MainWidget::deleteHooks()
{
    changed_vector_of_buttons.clear();
}

void MainWidget::keyPressEvent(QKeyEvent *event) {
    is_key_pressed += 1;
    QString txt = event->text();
    std::map<QString, std::tuple<QToolButton*, int, int>>::iterator button = all_buttons.find(txt);
    std::map<QString, std::tuple<QToolButton*, int, int>>::iterator num_button = all_buttons.find("numpad" + txt);
    if(button != all_buttons.end()){
        std::get<0>(button->second)->animateClick();
        keypressed(txt);
    }else if(num_button != all_buttons.end()){
        std::get<0>(num_button->second)->animateClick();
        keypressed("numpad" +txt);
    }else{
        QString txt = getRightStringOfButton(event);
        std::map<QString, std::tuple<QToolButton*, int, int>>::iterator button = all_buttons.find(txt);
        std::map<QString, std::tuple<QToolButton*, int, int>>::iterator num_button = all_buttons.find("numpad" + txt);
        if(button != all_buttons.end()){
            std::get<0>(button->second)->animateClick();
            keypressed(txt);
        }else if(num_button != all_buttons.end()){
            std::get<0>(num_button->second)->animateClick();
            keypressed("numpad" + txt);
        }
    }
}

