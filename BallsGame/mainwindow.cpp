#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 * Constructor for this Class
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isRunning = false;
    this->ui->graphicsView->setSceneRect(0,0,600,400);
    this->ui->graphicsView->setFixedSize(600, 400);

}

/**
 * Destructor for this Class
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Function on_creditsInButton_clicked
 *  Button on click - Add credits.
 */
void MainWindow::on_creditsInButton_clicked()
{
    this->creditsIn++;
    this->totalCredits = this->creditsIn - this->creditsOut;
    QString coinsString = QString::number(this->creditsIn);
    this->ui
        ->creditsInLabel
        ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Credits In: </span><span id='number'>" + coinsString + "</span></p></body></html>");
}

/**
 * Function on_creditsOutButton_clicked
 *  Button on click - Add credits out.
 */
void MainWindow::on_creditsOutButton_clicked()
{
    this->creditsOut=this->creditsIn;
    this->totalCredits = this->creditsIn - this->creditsOut;
    QString coinsString = QString::number(this->creditsOut);
    this->ui
        ->creditsOutLabel
        ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Credits Out: </span><span id='number'>" + coinsString + "</span></p></body></html>");

}

/**
 * Function on_creditsInButton_clicked
 *  Button on click - Starts the game.
 */
void MainWindow::on_startButton_clicked()
{
    // If the game started already when pressing button start pauses and then resumes the game
    // It only counts games played when the game really ends
    if ( this->totalCredits > 0 && gameState == 0 && !isRunning)
    {
        // Add out credits
        this->creditsOut++;
        this->totalCredits = this->creditsIn - this->creditsOut;
        QString coinsString = QString::number(this->creditsOut);
        this->ui
            ->creditsOutLabel
            ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Credits Out: </span><span id='number'>" + coinsString + "</span></p></body></html>");


        // Start the Game
        this->startGame();
    }else if ( gameState == 1 ){
        // pause game
        this->pauseGame();
    }else if ( gameState == 2){
        // Resume game
        this->resumeGame();
    }else {
        // Out of credits
        QMessageBox msgBox;
        msgBox.setText("You need credits to play this ball game!");
        msgBox.exec();
    }

}

/**
 * Function startGame
 *  Set the game state for Starting the game
 */
void MainWindow::startGame(){
    this->isRunning = true;
    this->gameState = 1;

    // Setting up the view
    this->runView();
}

/**
 * Function pauseGame
 *  Set the game state to pause the game
 */
void MainWindow::pauseGame(){
    this->isRunning = false;
    this->gameState = 2;
    QMessageBox msgBox;
    msgBox.setText("Game paused!");
    msgBox.exec();
}

/**
 * Function pauseGame
 *  Set the game state to resume the game
 */
void MainWindow::resumeGame(){
    this->isRunning = true;
    this->allBalls->restartTimer();
    this->gameState = 1;

    QMessageBox msgBox;
    msgBox.setText("Game resumed!");
    msgBox.exec();
}

/**
 * Function runView
 *  Setting the view and call the method to create the balls.
 */
void MainWindow::runView(){
    // Create Scene
    if ( this->scene == nullptr ){
        this->scene = new QGraphicsScene(this);
        this->scene->setSceneRect(0, 0, 600, 400);
    }else {
        this->scene->clear();
    }

    // Create Balls
    if ( this->allBalls == nullptr) {
        this->allBalls = new Balls(this->scene, this->isRunning, this->gamesPlayed, this->gameState, this->ui);
    }else {
        this->allBalls->clearBalls();
        this->allBalls->restartTimer();
    }

    // Set Scene to the view
    this->ui->graphicsView->setScene(this->scene);
}

// Keypressed Event Handler
/**
 * Function keyPressEvent
 *  Keypress Handler
 *  @args
 *  @ pe - the key event when a key is pressed.
 */
void MainWindow::keyPressEvent( QKeyEvent* pe )
{
    switch( pe->key() )
    {
        // S key - Starts the game
        case Qt::Key_S:
        {
            this->on_startButton_clicked();
            break;
        }
        // P key - Pause/Resumes the game
        case Qt::Key_P:
        {
            if( this->gameState == 1 ){
                this->pauseGame();
            }else if ( this->gameState == 2 ) {
                this->resumeGame();
            }
            break;
        }
        // + key - Add credits
        case Qt::Key_Plus:
        {
            this->on_creditsInButton_clicked();
            break;
        }
        // - key - remove credits
        case Qt::Key_Minus:
        {
            this->on_creditsOutButton_clicked();
            break;
        }
    }
}


