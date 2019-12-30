#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

#include <map>
#include <tuple>

#include "json_manager.h"

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
        QGridLayout *layout;
        QString activeButton;
        QToolButton* active_button;
        QLineEdit *display_old_layout;
        QLineEdit *display_new_layout;
        RemapperConf remapperConf;
        std::vector<QString> all_possible_buttons;
        std::map<std::string, std::vector<std::string>> changed_vector_of_buttons;
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
