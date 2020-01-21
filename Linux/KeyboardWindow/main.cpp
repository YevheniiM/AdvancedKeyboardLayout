#include <QRunnable>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QVector>
#include <QString>

#include <iostream>
#include <vector>
#include <string>

#include "Keyboard.h"
#include "Remapper.h"

QWaitCondition keyPressed;
QMutex mutex;
std::vector<QString> remaps;

auto mf = new SignalController();

class WorkerThread : public QThread
{
    void run() override
    {
        auto rmp = Remapper();
        rmp.listen(keyPressed, remaps, mf);
    }
public:
    std::function<void(void)> signal;
};


int main(int argc, char ** argv)
{
   WorkerThread *wt = new WorkerThread();
   QObject::connect(wt, &WorkerThread::finished, wt, &QObject::deleteLater);
   wt->start();

    while(true)
    {
        mutex.lock();
        keyPressed.wait(&mutex);
        auto loc_remaps = remaps;
        mutex.unlock();

        ButtonSuggest * app;
        app = new ButtonSuggest(argc, argv);
        QObject::connect(mf, &SignalController::Exit,
                         app, &ButtonSuggest::Exit);
        QObject::connect(mf, &SignalController::ChangeFocus,
                         app, &ButtonSuggest::ChangeFocus);
        app->remaps = &remaps;
        app->loadContent();
        app->showWin();
        app->exec();

    }
    return 0;
}
