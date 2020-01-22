#include "mainwindow.h"
#include "all_buttons.h"
#include "json_manager.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QToolButton>
#include <utility>
#include <functional>

extern const std::vector<std::vector<QString>> buttons;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    new_file(true), file_changed(false),
    is_key_pressed(0), ui(new Ui::MainWindow),
    activeKeyLayout(0)
{
    ui->setupUi(this);
    SetupStatusbar();
    filesMask = tr("Json Files (*.json);;");
    app_name =  windowTitle();
    for(int i = 0; i < 6; ++i){
        keyMaps.emplace_back();
    }
    for(size_t index = 0; index < buttons.size(); ++index){
        all_buttons.emplace_back();
        int horizontal = 0;
        for(size_t new_index = 0; new_index < buttons.at(index).size(); ++new_index){
            size_t len = 1;
            if(!buttons.at(index).at(new_index).size()){
                continue;
            }
            if(new_index == 0){
                // create new Button and set default text and policy
                QToolButton *button = new QToolButton();
                button->setText(buttons.at(index).at(new_index));
                button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                if(index == 0){
                    QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_Row_1_clicked()));
                }else if(index == 1){
                    QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_Row_2_clicked()));
                }else if(index == 2){
                    QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_Row_3_clicked()));
                }else if(index == 3){
                    QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_Row_4_clicked()));
                }else if(index == 4){
                    QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_Row_5_clicked()));
                }else if(index == 5){
                    QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_Row_6_clicked()));
                }
                ui->Rows->addWidget(button);
                ui->Rows->setStretch(index, 1);
            }else{
                if(buttons.at(index).at(new_index) == "backspace" || buttons.at(index).at(new_index) == "enter" || buttons.at(index).at(new_index) == "shift"){
                    len = 3;
                }else if(buttons.at(index).at(new_index) == "tab" || buttons.at(index).at(new_index) == "\\" || buttons.at(index).at(new_index) == "caps lock"){
                    len = 2;
                }if(buttons.at(index).at(new_index) == "right shift" || buttons.at(index).at(new_index) == "right ctrl"){
                    len = 2;
                }if(buttons.at(index).at(new_index) == "space"){
                    len = 6;
                }
                QToolButton *button = make_button(buttons.at(index).at(new_index).toUpper(), index, horizontal, 1, len);
                all_buttons.at(index).push_back(button);
                horizontal += len;
            }
        }
    }
    keyMaps.at(activeKeyLayout).is_multiple = false;
    keyMaps.at(activeKeyLayout).mode = "Single";
    keyMaps.at(activeKeyLayout).conf_value = 0;
    ui->NTimes->setEnabled(false);
    ui->Hold->setEnabled(false);
    ui->NTimes->setChecked(false);
    ui->Hold->setChecked(false);
    ui->period->setEnabled(false);
    activeRow = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionHelp_triggered()
{
    QMessageBox aboutBox;
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.setWindowTitle(app_name);
    aboutBox.setText(tr("Smart keyboard layout."));
    aboutBox.setInformativeText(tr("Developed for operating system`s course."));
    aboutBox.setStandardButtons(QMessageBox::Ok);
    aboutBox.exec();
}

int MainWindow::askToSaveChanged(const QString& title)
{
    QMessageBox quitMsg;
    quitMsg.setWindowTitle(app_name);
    quitMsg.setText(title);
    quitMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::Save | QMessageBox::Cancel);
    quitMsg.setDefaultButton(QMessageBox::Cancel);
    return quitMsg.exec();
}

void MainWindow::on_actionExit_triggered()
{
    if(file_changed)
    {
        switch( askToSaveChanged(tr("Current changes are not saved. \nDo you really want to quit?")) )
        {
        case QMessageBox::Yes:
            QApplication::instance()->quit();
            break;
        case QMessageBox::Save:
            emit ui->actionSave->triggered();
            break;
        }
    }else
    {
        QApplication::instance()->quit();
    }
}

void MainWindow::closeEvent(QCloseEvent *bar)
{
    emit ui->actionExit->triggered();
    // If we are there --- user chose to ignore exit button.
    bar->ignore();
}

void MainWindow::SetupStatusbar()
{
    //Status bar fields
    sbFilename = new QLabel("");
    statusBar()->addWidget(sbFilename);

    sbFileChanged = new QLabel(tr("      "));
    sbFileChanged->setMinimumSize( sbFileChanged->sizeHint() );
    sbFileChanged->setAlignment(Qt::AlignCenter);
    sbFileChanged->setToolTip(tr("Is file changed?"));
    statusBar()->addPermanentWidget(sbFileChanged);
}

void MainWindow::on_actionOpen_triggered()
{
    if(file_changed)
    {
        switch( askToSaveChanged(tr("Current changes are not saved."
                                    "\nDo you really want to throw out them?")) )
        {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Save:
            emit ui->actionSave->triggered();
            break;
        }
    }

    setFileName(QFileDialog::getOpenFileName(this, tr("Open File"), QString(), filesMask));

    if (!curFileName.isEmpty()) {
//        read_to_json(curFileName.toStdString(), pid, keyMaps);
    }
}

void MainWindow::setFileName(const QString& fileName)
{
    curFileName = fileName;
    QFileInfo curFI(curFileName);
    sbFilename->setText( curFI.fileName() );
    sbFilename->setToolTip( curFI.canonicalFilePath() );
}

QToolButton* MainWindow::make_button(const QString &text, int x, int y, int height, int width){
    // create new Button and set default text and policy
    QToolButton *button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->KeyboardSettings->addWidget(button, x, y, height, width);
    if(keyMaps.at(activeKeyLayout).search(text)){
        for(int i = 0; i < 6; ++i){
          keyMaps.at(i).all_buttons[text] = std::make_tuple(button, x, y);
        }
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(keypressed()));
    }
    return button;
}

QString MainWindow::getRightStringOfButton(const QKeyEvent *event){
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
    return "";
}


void MainWindow::keypressed(const QString &text)
{
    // e.g. casting to the class you know its connected with
    QToolButton* button = nullptr;
    if(is_key_pressed == 0){
        button = qobject_cast<QToolButton*>(sender());
    }
    QString txt = text.toUpper();
    if(button != nullptr)
    {
        txt = button->text().toUpper();
    }

    if(txt != ""){
        if(button != nullptr && keyMaps.at(activeKeyLayout).activeButton == ""){
            keyMaps.at(activeKeyLayout).activeButton = txt;
            ui->ActiveButton->setText(txt);
        }else if(keyMaps.at(activeKeyLayout).activeButton != ""){
            QToolButton *new_button = std::get<0>(keyMaps.at(activeKeyLayout).all_buttons.find(keyMaps.at(activeKeyLayout).activeButton)->second);
            if(!keyMaps.at(activeKeyLayout).is_multiple){
                keyMaps.at(activeKeyLayout).changed_vector_of_buttons[keyMaps.at(activeKeyLayout).activeButton.toStdString()].clear();
                new_button->setText(txt);
            }
            keyMaps.at(activeKeyLayout).changed_vector_of_buttons[keyMaps.at(activeKeyLayout).activeButton.toStdString()].push_back(txt.toStdString());
            keyMaps.at(activeKeyLayout).activeButton = "";
            ui->ActiveButton->setText("Active button");
        }
    }
    if(is_key_pressed > 0 && button == nullptr && text == ""){
        is_key_pressed -= 1;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    is_key_pressed += 1;
    QString txt = event->text().toUpper();
    std::map<QString, std::tuple<QToolButton*, int, int>>::iterator button = keyMaps.at(activeKeyLayout).all_buttons.find(txt);
    if(button != keyMaps.at(activeKeyLayout).all_buttons.end()){
        std::get<0>(button->second)->animateClick();
        keypressed(txt);
    }else{
        QString txt = getRightStringOfButton(event).toUpper();
        std::map<QString, std::tuple<QToolButton*, int, int>>::iterator button = keyMaps.at(activeKeyLayout).all_buttons.find(txt);
        if(button != keyMaps.at(activeKeyLayout).all_buttons.end()){
            std::get<0>(button->second)->animateClick();
            keypressed(txt);
        }
    }
}

void MainWindow::on_MultipleKeys_clicked()
{
    keyMaps.at(activeKeyLayout).is_multiple = true;
    keyMaps.at(activeKeyLayout).mode = "Multiple";
    keyMaps.at(activeKeyLayout).conf_value = 0.5;
    ui->NTimes->setEnabled(true);
    ui->Hold->setEnabled(true);
    ui->NTimes->setChecked(true);
    ui->Hold->setChecked(false);
    ui->period->setEnabled(true);
    ui->period->setValue(0.5);
}

void MainWindow::on_SingleKeys_clicked()
{
    keyMaps.at(activeKeyLayout).is_multiple = false;
    keyMaps.at(activeKeyLayout).mode = "Single";
    keyMaps.at(activeKeyLayout).conf_value = 0;
    ui->NTimes->setEnabled(false);
    ui->Hold->setEnabled(false);
    ui->NTimes->setChecked(false);
    ui->Hold->setChecked(false);
    ui->period->setEnabled(false);
}

void MainWindow::on_actionSave_triggered()
{
    write_to_json(curFileName.toStdString(), 12, keyMaps);
}

void MainWindow::ClearKeyboard(){
    for(size_t index = 0; index < buttons.size(); ++index){
        int minus = -1;
        if(index == 0)
            minus = -2;
        for(size_t index_x = 0; index_x < (buttons.at(index).size() + minus); ++index_x){
            auto item = keyMaps.at(activeKeyLayout).changed_vector_of_buttons.find(all_buttons.at(index).at(index_x)->text().toUpper().toStdString());
            if(keyMaps.at(activeKeyLayout).mode == "Multiple" || item == keyMaps.at(activeKeyLayout).changed_vector_of_buttons.end()){
                all_buttons.at(index).at(index_x)->setText(buttons.at(index).at(index_x+1).toUpper());
            }else{
                all_buttons.at(index).at(index_x)->setText(item->second.at(0).c_str());
            }
        }
    }
}

void MainWindow::on_FirstLayout_clicked()
{
    activeKeyLayout = 0;
    ClearKeyboard();
}

void MainWindow::on_pushButton_5_clicked()
{
    activeKeyLayout = 1;
    ClearKeyboard();
}

void MainWindow::on_pushButton_4_clicked()
{
    activeKeyLayout = 2;
    ClearKeyboard();
}

void MainWindow::on_pushButton_3_clicked()
{
    activeKeyLayout = 3;
    ClearKeyboard();
}

void MainWindow::on_pushButton_clicked()
{
    activeKeyLayout = 4;
    ClearKeyboard();
}

void MainWindow::on_pushButton_2_clicked()
{
    activeKeyLayout = 5;
    ClearKeyboard();
}

void MainWindow::change_two_rows(size_t last_row, size_t current_row){
    for(size_t index = 1; index < buttons.at(last_row).size() && index < buttons.at(current_row).size(); ++index){
        is_key_pressed += 1;
        QString txt = buttons.at(last_row - 1).at(index).toUpper();
        std::map<QString, std::tuple<QToolButton*, int, int>>::iterator button = keyMaps.at(activeKeyLayout).all_buttons.find(txt);
        if(button != keyMaps.at(activeKeyLayout).all_buttons.end()){
            std::get<0>(button->second)->animateClick();
            keypressed(txt);
        }
        is_key_pressed += 1;
        txt = buttons.at(current_row - 1).at(index).toUpper();
        button = keyMaps.at(activeKeyLayout).all_buttons.find(txt);
        if(button != keyMaps.at(activeKeyLayout).all_buttons.end()){
            std::get<0>(button->second)->animateClick();
            keypressed(txt);
        }
    }
}

void MainWindow::on_Row_1_clicked()
{
    if(activeRow == 0 || activeRow == 1){
        activeRow = 1;
        ui->LastActiveRow->setText("First row");
    }else{
        change_two_rows(activeRow, 1);
        activeRow = 0;
        ui->LastActiveRow->setText("LastActiveRow");
    }
}

void MainWindow::on_Row_2_clicked()
{
    if(activeRow == 0 || activeRow == 2){
        activeRow = 2;
        ui->LastActiveRow->setText("Second row");
    }else{
        change_two_rows(activeRow, 2);
        activeRow = 0;
        ui->LastActiveRow->setText("LastActiveRow");
    }
}

void MainWindow::on_Row_3_clicked()
{
    if(activeRow == 0 || activeRow == 3){
        activeRow = 3;
        ui->LastActiveRow->setText("Third row");
    }else{
        change_two_rows(activeRow, 3);
        activeRow = 0;
        ui->LastActiveRow->setText("LastActiveRow");
    }
}

void MainWindow::on_Row_4_clicked()
{
    if(activeRow == 0 || activeRow == 4){
        activeRow = 4;
        ui->LastActiveRow->setText("Fourth row");
    }else{
        change_two_rows(activeRow, 4);
        activeRow = 0;
        ui->LastActiveRow->setText("LastActiveRow");
    }
}

void MainWindow::on_Row_5_clicked()
{
    if(activeRow == 0 || activeRow == 5){
        activeRow = 5;
        ui->LastActiveRow->setText("Fifth row");
    }else{
        change_two_rows(activeRow, 5);
        activeRow = 0;
        ui->LastActiveRow->setText("LastActiveRow");
    }
}

void MainWindow::on_Row_6_clicked()
{
    if(activeRow == 0 || activeRow == 6){
        activeRow = 6;
        ui->LastActiveRow->setText("Sixth row");
    }else{
        change_two_rows(activeRow, 6);
        activeRow = 0;
        ui->LastActiveRow->setText("LastActiveRow");
    }
}
