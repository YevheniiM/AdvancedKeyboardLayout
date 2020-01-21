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

protected:
    void closeEvent(QCloseEvent *bar) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool clear;
    bool new_file;
    QString app_name;
    bool file_changed;
    QString filesMask;
    int is_key_pressed;
    Ui::MainWindow *ui;
    QString curFileName;
    size_t activeKeyLayout;
    void SetupStatusbar();
    void setFileName(const QString& fileName);
    QString getRightStringOfButton(const QKeyEvent *event);
    std::vector<Keymap> keyMaps;
    void make_button(const QString &text, int x, int y, int height, int width);
    QLabel* sbFilename, *sbFileSymbols, *sbFileCol, *sbFileRow, *sbFileChanged;
    int askToSaveChanged(const QString& title);
};
#endif // MAINWINDOW_H
