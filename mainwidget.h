#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

#include <map>
#include <tuple>

#include "customhook.h"

VirtualKeyMapper remapper;

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
        QString activeButton;
        CustomHook hook;
        QGridLayout *layout;
        QLineEdit *display_old_layout;
        QLineEdit *display_new_layout;
        std::map<QString, std::string> changed_buttons;
        QString getRightStringOfButton(const QKeyEvent *event);
        std::map<QString, std::tuple<QToolButton*, int, int>> all_buttons;
        void make_button(const QString &text, int x, int y, int width, int height);
    private slots:
        void keypressed(const QString &text="");
};
#endif // MAINWIDGET_H
