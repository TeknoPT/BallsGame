#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_creditsInButton_clicked()
{
    this->creditsIn++;
    this->totalCredits = this->creditsIn - this->creditsOut;
    QString coinsString = QString::number(this->creditsIn);
    this->ui
        ->creditsInLabel
        ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Credits In: </span><span id='number'>" + coinsString + "</span></p></body></html>");
}

void MainWindow::on_creditsOutButton_clicked()
{
    this->creditsOut++;
    this->totalCredits = this->creditsIn - this->creditsOut;
    QString coinsString = QString::number(this->creditsOut);
    this->ui
        ->creditsOutLabel
        ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Credits Out: </span><span id='number'>" + coinsString + "</span></p></body></html>");

}

void MainWindow::on_startButton_clicked()
{

    // If the game started already when pressing button start pauses and then resumes the game
    // It only counts games played when the game really ends

    if ( this->totalCredits > 0 && gameState == 0 && !isRunning)
    {
        // Add out credits
        this->on_creditsOutButton_clicked();

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

void MainWindow::startGame(){
    this->isRunning = true;
    this->gameState = 1;
    QMessageBox msgBox;
    msgBox.setText("Lets play a game!");
    msgBox.exec();
    this->runView();
}

void MainWindow::pauseGame(){
    this->isRunning = true;
    this->gameState = 2;
    QMessageBox msgBox;
    msgBox.setText("Game paused!");
    msgBox.exec();
}

void MainWindow::resumeGame(){
    this->isRunning = true;
    this->gameState = 1;
    QMessageBox msgBox;
    msgBox.setText("Game resumed!");
    msgBox.exec();
}

void MainWindow::endGame(){
    // End game add games played
    this->isRunning = false;
    this->gameState = 0;
    this->gamesPlayed++;
    QString gamesPlayed = QString::number(this->gamesPlayed);
    this->ui
        ->gamesPlayedLabel
        ->setText("<html><head/><body><p align='center'><span style=' font-weight:600;'>Games played: </span><span id='number'>" + gamesPlayed + "</span></p></body></html>");
}

void MainWindow::runView(){
    // Create Scene
    this->scene = new QGraphicsScene(this);

    // Create a rectange
    QRect rect;
    QSize size;
    size.setWidth(50);
    size.setHeight(50);
    rect.setSize(size);
    QGraphicsEllipseItem* neEllipse = nullptr;
    // Create elipse
    for (int i = 0; i< 10 ;i++) {
        this->update();
        if (neEllipse != nullptr) this->scene->removeItem(neEllipse);

        neEllipse = new QGraphicsEllipseItem(30,30, 50*i, 50*i);
        (*neEllipse).setX(110*i);
        this->scene->addItem(neEllipse);


    }
    //this->ellipse = new QGraphicsEllipseItem(30,30, 50, 50);

    // Display everything
    this->scene->addRect(rect);

    // Set Scene
    this->ui->graphicsView->setScene(this->scene);
}


// Keypressed Event Handler
void MainWindow::keyPressEvent( QKeyEvent* pe )
{
    switch( pe->key() )
    {
        case Qt::Key_S:
        {
            this->on_startButton_clicked();
            break;
        }
        case Qt::Key_P:
        {
            if( this->gameState == 1 ){
                this->pauseGame();
            }else if ( this->gameState == 2 ) {
                this->resumeGame();
            }

            break;
        }
        case Qt::Key_E:
        {
            if( this->isGameValid() )
                this->endGame();
            break;
        }
        case Qt::Key_Plus:
        {
            this->on_creditsInButton_clicked();
            break;
        }
        case Qt::Key_Minus:
        {
            this->on_creditsOutButton_clicked();
            break;
        }
    }
}

bool MainWindow::isGameValid()
{
    if (isRunning && gameState != 0)
        return true;
    else
        return false;
}
