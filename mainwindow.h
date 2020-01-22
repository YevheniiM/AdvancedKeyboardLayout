#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include "keymap.h"
#include <QMainWindow>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_actionHelp_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void keypressed(const QString &text="");
    void on_MultipleKeys_clicked();

    void on_SingleKeys_clicked();

    void on_actionSave_triggered();

    void on_FirstLayout_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Row_1_clicked();

    void on_Row_2_clicked();

    void on_Row_3_clicked();

    void on_Row_4_clicked();

    void on_Row_5_clicked();

    void on_Row_6_clicked();

protected:
    void closeEvent(QCloseEvent *bar) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    int pid;
    bool clear;
    bool new_file;
    int activeRow;
    QString app_name;
    bool file_changed;
    QString filesMask;
    int is_key_pressed;
    Ui::MainWindow *ui;
    QString curFileName;
    void ClearKeyboard();
    void SetupStatusbar();
    size_t activeKeyLayout;
    std::vector<Keymap> keyMaps;
    void setFileName(const QString& fileName);
    QString getRightStringOfButton(const QKeyEvent *event);
    std::vector<std::vector<QToolButton*>> all_buttons;
    void change_two_rows(size_t last_row, size_t current_row);
    QToolButton* make_button(const QString &text, int x, int y, int height, int width);
    QLabel* sbFilename, *sbFileSymbols, *sbFileCol, *sbFileRow, *sbFileChanged;
    int askToSaveChanged(const QString& title);
};
#endif // MAINWINDOW_H
