#ifndef SPELLCORRECTION_H
#define SPELLCORRECTION_H
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QMessageBox>

#include <unistd.h>
#include <sys/wait.h>

class SpellCorrection
{
public:
//    SpellCorrection();
    QString buffer {}, words {}, puncts {}, correctText {};

    SpellCorrection& operator += (const std::string & new_character)
    {
        return operator += (QString::fromStdString(new_character));
    }

    SpellCorrection& operator += (const QString & new_character)
    {
        if (buffer.size() > 250)
            buffer.remove(0, 1);
        buffer += new_character;
        for (auto & s_end : {".", "!", "?"})
            if (new_character == s_end)
                correctText = correct();
        return *this;
    }

private:

    void parseBuffer()
    {
        QString words_buf;
        QChar last_symb;
        buffer.replace("space", " ");
        for (auto & symbol: buffer)
        {
            if (symbol.isPunct())
            {
                puncts += symbol;
                words += words_buf += " ";
                words_buf = "";
            }
            else
            {
                if (symbol != " ")
                    words_buf += symbol;
                if (symbol == " " && !last_symb.isPunct())
                {
                    puncts += " ";
                    words += words_buf += " ";
                    words_buf = "";
                }
            }
            last_symb = symbol;
        }
    }

    void forkExec()
    {
        pid_t pid = fork();

        if ( pid == -1 )
            throw std::runtime_error("Failed to fork");
        else if ( pid > 0 )
        {
            int status;
            waitpid(pid, &status, 0);
        }
        else
        {
              QByteArray ba = words.toLocal8Bit();
              char *words_arg = ba.data();
            char * args[4] = {"/usr/bin/python3",
                              "DL-approaches-for-spell-correction/client.py",
                              words_arg,
//                              ">",
//                              "res.txt",
                              nullptr};
            execve("/usr/bin/python3", args, nullptr);
       }
    }

    QString loadCorrect()
    {
        QFile f("correct.txt");
        if (!f.open(QFile::ReadOnly | QFile::Text))
            qDebug() << "Cannot open the file ";
        return QTextStream(&f).readAll();
    }

    int showDialog(const QString & correctText)
    {
//        QMessageBox msgBox;
//        msgBox.setText("Do you want to correct text?");
//        msgBox.setInformativeText(correctText);
//        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
//        msgBox.setDefaultButton(QMessageBox::Save);
//        int ret = msgBox.exec();
//        switch (ret)
//        {
//        case QMessageBox::Save:
//            return 1;
//        case QMessageBox::Discard:
//            return 0;
//        default:
//            return 0;
//        }
        return 1;
    }

    QString correct()
    {
        parseBuffer();
        forkExec();
        auto correctText_ = loadCorrect();
        return (showDialog(correctText_)) ? correctText_ : "";
    }


};

#endif // SPELLCORRECTION_H
