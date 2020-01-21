#include "Keyboard.h"
#include <QLabel>
#include <QThread>
#include <QPushButton>
#include <QDebug>

ButtonSuggest::ButtonSuggest(int &argc, char ** argv)
: QApplication(argc, argv), currentlySelectedIndex(0, 0)
{
}

void ButtonSuggest::loadContent(int newFocus)
{

    window = new QMainWindow();

    window->setWindowFlags(window->windowFlags() | Qt::Tool
                           | Qt::FramelessWindowHint | Qt::Popup
                           | Qt::WindowStaysOnTopHint);

    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    window->setContentsMargins(0, 0, 0, 0);

//    timer = new QTimer();
//    timer->setSingleShot(true);
//    connect(timer, &QTimer::timeout, this, &ButtonSuggest::filterSuggestions);
    //timer.timeout.connect(filterSuggestions);

//    qDebug() << "Loading for: ";
    buttons.clear();
    for (auto & letter : *remaps)
    {
        buttons.push_back( new QLabel(window) );
        buttons.back()->setText(letter);
        buttons.back()->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        buttons.back()->setAlignment(Qt::AlignCenter);
        buttons.back()->setStyleSheet(nonActiveButton);
        layout->addWidget(buttons.back());
    }
    buttons[newFocus]->setStyleSheet(activeButton);
    currentFocus = newFocus;

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    window->setFixedSize(60 * buttons.size(), 60);
    window->setCentralWidget(widget);

}

void ButtonSuggest::showWin() {
    window->show();
    window->raise();
}

void ButtonSuggest::Exit() {
    window->close();
    exit();
}

void ButtonSuggest::ChangeFocus(int newFocus)
{
    window->close();
    loadContent(newFocus % remaps->size());
    showWin();
}

void ButtonSuggest::keyEventCatcher(QKeyEvent e) {

    int key = e.key();
    Qt::KeyboardModifiers modifiers = e.modifiers();

    if (key == Qt::Key_Escape) {
        quit();
    }

    if (key == Qt::Key_Down) {
        if (suggestionList->count() == 0) {
            currentlySelectedIndex.set(0);
        } else if (suggestionList->count() == 1) {
            currentlySelectedIndex.set(0);
            suggestionList->setCurrentRow(0);
            entry->setText(suggestionList->item(0)->text());
        } else {
            currentlySelectedIndex.set(currentlySelectedIndex.get() + 1);
            suggestionList->setCurrentRow(currentlySelectedIndex.get());
            entry->setText(suggestionList->currentItem()->text());
        }
    }

    if (key == Qt::Key_Up) {
        if (suggestionList->count() == 0) {
            currentlySelectedIndex.set(0);
        } else if (suggestionList->count() == 1) {
            currentlySelectedIndex.set(0);
            suggestionList->setCurrentRow(0);
            entry->setText(suggestionList->item(0)->text());
        } else {
            currentlySelectedIndex.set(currentlySelectedIndex.get() - 1);
            suggestionList->setCurrentRow(currentlySelectedIndex.get());
            entry->setText(suggestionList->currentItem()->text());
        }
    }

    if (key == Qt::Key_Enter || key == Qt::Key_Return) {
//		if (modifiers & Qt::AltModifier) {
//			std::cout << "Alt+Enter: disabling processing" << std::endl;
//			this->opt_processing = false;
//		}
//		applySuggestion();
    }

    if (key == Qt::Key_Delete) {
        if ((modifiers & Qt::ShiftModifier) && (modifiers & Qt::ControlModifier)) {
//			std::cout << "Ctrl+Shift+Delete: adding to ignore list" << std::endl;
            addSuggestionToIgnoreList();
        }

        if (modifiers & Qt::ShiftModifier) {
//			std::cout << "Shift+Delete: removing from history" << std::endl;
            removeSuggestionFromHistory();
        }
    }

}

void ButtonSuggest::textEdited(const QString &text) {
    timer->start(TYPE_SUGGEST_DELAY);
}

void ButtonSuggest::populateSuggestions(std::vector<std::string> suggestions) {

        suggestionList->clear();

        for (std::string &x : suggestions) {
            suggestionList->addItem(QString::fromStdString(x));
            //QListWidgetItem(QString::fromStdString(x), suggestionList);
        }

        currentlySelectedIndex.setMax(suggestions.size());
        currentlySelectedIndex.set(0);
        suggestionList->setCurrentRow(0);

}

void ButtonSuggest::filterSuggestions() {

//	std::string text = entry->text().toStdString();
//	if (text == "") {
//		populateSuggestions(allWords);
//	} else {
//		if (opt_custom_words_only) {
//			populateSuggestions(server->get_custom_words_only(text));
//		} else {
//			populateSuggestions(server->get_suggestions(text, opt_languages));
//		}
//	}

}

std::string ButtonSuggest::getCurrentSuggestion() {

//	if (suggestionList->count() == 0) {
//		return entry->text().toStdString();
//	} else {
//		return suggestionList->currentItem()->text().toStdString();
//	}

}

void ButtonSuggest::applySuggestion() {

    window->hide();

    std::string text = getCurrentSuggestion();

    if (text == "") {
        quit();
    }

//	if (opt_history) {
//		server->history_increment(text);
//	}

//	std::cout << text << std::endl;

//	if (opt_processing) {
//		text = server->process_suggestion(text);
//	}


//	std::cout << text << std::endl;

//	server->type_text(text);
//	server->reload_configs();

    quit();

}

void ButtonSuggest::removeSuggestionFromHistory() {
//	server->history_remove(getCurrentSuggestion());
}

void ButtonSuggest::addSuggestionToIgnoreList() {
//	server->ignore_list_add(getCurrentSuggestion());
}

ButtonSuggest::~ButtonSuggest() {}
