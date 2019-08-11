#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QSize>
#include <QKeyEvent>
#include <array>
#include <QTimer>
#include "ball.h"
#include "balls.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Keypressed
    void keyPressEvent(QKeyEvent *e);
    
    // Constructor | Creating the MainWindow
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    // Function button on click creadits in.
    void on_creditsInButton_clicked();

    // Function button on click creadits out.
    void on_creditsOutButton_clicked();

    // Function button on click start game.
    void on_startButton_clicked();

    //void endGame();

private:
    // Main
    QGraphicsScene *scene = nullptr;

    Ui::MainWindow *ui;
    // Variables
    int creditsIn = 0;
    int creditsOut = 0;
    int totalCredits = 0;
    int gamesPlayed = 0;
    bool isRunning = false;
    int gameState = 0; // 0 - not running | 1 - running | 2 - paused

    // Methods
    void startGame();
    void pauseGame();
    void resumeGame();
    void runView();
    bool isGameValid();

    //Balls
    Balls * allBalls = nullptr;

};

#endif // MAINWINDOW_H
