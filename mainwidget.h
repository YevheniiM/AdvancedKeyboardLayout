#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

#include <map>
#include <tuple>

#ifdef __linux__
    //linux code goes here
#elif _WIN32
       #include "customhook.h"
#endif

class MainWidget : public QWidget
{
    Q_OBJECT
    public:
        MainWidget();
        ~MainWidget() override;
    protected:
        void keyPressEvent(QKeyEvent *event) override;
    private:
        bool clear;
        int is_key_pressed;
        QString activeButton;
#ifdef __linux__
    //linux code goes here
#elif _WIN32
        CustomHook hook;
#endif

        QToolButton* active_button;
        QGridLayout *layout;
        QLineEdit *display_old_layout;
        QLineEdit *display_new_layout;
        std::map<QString, QString> changed_buttons;
        std::vector<QString> all_possible_buttons;
        QString getRightStringOfButton(const QKeyEvent *event);
        std::map<QString, std::tuple<QToolButton*, int, int>> all_buttons;
        void make_button(const QString &text, int x, int y, int width, int height);
        QToolButton* make_system_button(const QString &text, int x, int y, int height, int width);
    private slots:
        void keypressed(const QString &text="");
        void apply();
        void deleteHooks();
};
#endif // MAINWIDGET_H
