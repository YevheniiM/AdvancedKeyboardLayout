#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QLabel>

#include "Index.h"
#include "EventCatcher.h"

#define TYPE_SUGGEST_DELAY 200
class SignalController : public QObject
{
    Q_OBJECT
signals:
    void Exit(void);
    void ChangeFocus(int);
};
class ButtonSuggest : public QApplication
{
    Q_OBJECT
public:
    explicit ButtonSuggest(int &argc, char ** argv);
    ~ButtonSuggest();
    void loadContent(int newFocus=0);
    void showWin();
    void closeWin();
    void startWorkInAThread();
    std::vector<QString> * remaps;

protected:
    std::vector<QLabel *> buttons;
    int currentFocus {0};
    QString nonActiveButton = "border-radius: 25px;"
                           "background: white;"
                           "color: #4A0C46;";
    QString activeButton = "border-radius: 25px;"
                           "background: gray;"
                           "color: #4A0C46;";

private:
    void populateSuggestions(std::vector<std::string> suggestions);
    void filterSuggestions();
    std::string getCurrentSuggestion();
    void applySuggestion();
    void removeSuggestionFromHistory();
    void addSuggestionToIgnoreList();
    void textEdited(const QString &text);
    void keyEventCatcher(QKeyEvent event);
    void adjustSizes();

//	TextSuggestServerIFace * server;
    Index currentlySelectedIndex;
    std::vector<std::string> allWords;

    std::string opt_word;
    bool opt_history;
    std::vector<std::string> opt_languages;
    bool opt_auto_detect_language;
    bool opt_selection;
    bool opt_auto_selection;
    bool opt_custom_words_only;
    bool opt_processing;

    QMainWindow * window;
    QWidget * mainWidget;
    QHBoxLayout * layout;
    QTimer * timer;
    QListWidget * suggestionList;
    EventCatcher * entry;

public slots:
    void Exit();
    void ChangeFocus(int);
};
#endif // MAINWINDOW_H
