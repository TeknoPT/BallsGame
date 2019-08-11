#ifndef BALLS_H
#define BALLS_H

#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "ball.h"

namespace Ui {
    class MainWindow;
}
class MainWindow;

/**
 * Class Balls
 * For creating all the balls.
 */
class Balls : public QObject
{
    Q_OBJECT
public:
    // Constructor
    explicit Balls(QGraphicsScene * newScene, bool & vIsRunning, int & gamesPlayed, int & gameState, Ui::MainWindow* ui, QObject *parent = nullptr);
    void setScene(QGraphicsScene * newScene);
    void restartTimer();
    void clearBalls();

    // Balls
    Ball* balls[50];

public slots:
    void createBall();
    void endGame();

private:
    bool & isRunning;
    QGraphicsScene* scene;
    Ui::MainWindow * pUi;

    // Reference in memory Variables
    int & gamesPlayed;
    int & gameState; // 0 - not running | 1 - running | 2 - paused

    // Ball Variables
    int ballID = 0;
    int timerSpeed = 1;
    int ballFireRate = 500;
    int ballFireCounter = 0;
    QTimer * ballTimer;

    // Methods
    bool isGameValid();

};

#endif // BALLS_H
