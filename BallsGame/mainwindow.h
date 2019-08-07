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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent *e);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals: // Event
       void clickAddCoins();

private slots:
       void on_creditsInButton_clicked();

       void on_creditsOutButton_clicked();

       void on_startButton_clicked();

private:
    // Main
    QGraphicsScene *scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;

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
    void endGame();
    void runView();
    bool isGameValid();
};

#endif // MAINWINDOW_H
