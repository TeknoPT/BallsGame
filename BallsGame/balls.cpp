#include "balls.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * Constructor for this Class
 *  @args  
 *  @ newScene - the scene we are working on.
 *  @ vIsRunning - pointer to the main isRunning, so when stops, it stops all the things.
 *  @ parent - The parent object of this class.
 */
Balls::Balls(QGraphicsScene * newScene, bool & vIsRunning, int & gamesPlayed, int & gameState, Ui::MainWindow * pUi,QObject *parent) :
    QObject(parent), isRunning(vIsRunning), pUi(pUi), gamesPlayed(gamesPlayed), gameState(gameState)
{
    // Set the scene
    this->scene = newScene;

    // Reset Balls
    this->clearBalls();

    // Creating the timer for fireing the ball
    ballTimer = new QTimer();
    ballTimer->setInterval(this->timerSpeed);

    // Setting up the thread so it runs the createBall method.
    connect(ballTimer, SIGNAL(timeout()), this, SLOT(createBall()));

    // Starts the timer.
    ballTimer->start();
}

/**
 * Method for creating which ball
 * when the ballFireCounter hits 500;
 * It generates a new ball
 * This method runs every milisecond
 */
void Balls::createBall(){

    // It only counts when 
    if( this->isRunning )
    {
       this->ballFireCounter++;
    }

    // Verifying all the condition for the ball creation. 
    if ( this->ballFireCounter >= this->ballFireRate && ballID < 50 && this->isRunning){
        this->ballFireCounter=0;
        balls[ballID] = new Ball(ballID, 300, 150, isRunning);
        this->scene->addItem(balls[ballID]);
        ballID++;
    }else if(!this->isRunning){
        ballTimer->stop();
    }

    if( balls[49] != nullptr){
        if (balls[49]->endedPath){
            // endGame
            ballTimer->stop();
            this->endGame();
        }
    }
}

/**
 *  Setter 
 *   @args
 *   @QGraphicsScene * newScene - For setting the scene.
 */
void Balls::setScene(QGraphicsScene * newScene){
    this->scene = newScene;
}

// Restarts the timer.
void Balls::restartTimer(){
    ballTimer->start();
}

/**
 * Function pauseGame
 *  Set the game state to end the game
 */
void Balls::endGame(){
    // End game add games played
    this->isRunning = false;
    this->gameState = 0;
    this->gamesPlayed++;
    this->scene->clear();
    this->clearBalls();
    QString gamesPlayed = QString::number(this->gamesPlayed);
    this->pUi->gamesPlayedLabel
        ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Games played: </span><span id='number'>" + gamesPlayed + "</span></p></body></html>");
    QMessageBox msgBox;
    msgBox.setText("Game ended!");
    msgBox.exec();
}

/**
 * Function isGameValid
 *  Returns if the game is valid to start or not.
 */
bool Balls::isGameValid()
{
    if (this->isRunning && gameState != 0)
        return true;
    else
        return false;
}

void Balls::clearBalls(){
    for (int i = 0;i < 50;i++) {
        this->balls[i] = nullptr;
    }
    this->ballID = 0;
}
