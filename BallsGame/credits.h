#ifndef CREDITS_H
#define CREDITS_H

#include <QObject>
#include <QString>

class Credits : public QObject
{
    Q_OBJECT


    public slots: // handler
       void addCoins();

};

#endif // CREDITS_H
