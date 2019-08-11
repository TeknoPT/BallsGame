#include <QTimer>
#include "ball.h"
#include <QRandomGenerator>
#include <array>

/**
 * Constructor for this Class
 *  @args  
 *  @ id - id of the ball
 *  @ x - X position of the ball
 *  @ y - Y position of the ball
 *  @ isRunning - pointer to the main isRunning, so when stops, it stops all the things.
 */
Ball::Ball(int id, int x, int y, bool & isRunning) : isRunning(isRunning)
{
    // Set  the id of this ball
    this->id = id;

    // Draw the ball
    setRect(x,y, 10, 10);

    // Set the random seed to allways be random.
    srand(time(nullptr));

    // Creating random color for the ball
    QColor color;
    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;
    // qDebug("\nRed:%d\nGreen:%d\nBlue:%d",red,green,blue);
    color.setRgb(red,green,blue);

    // Create a brush
    // And set the brush with coler and style
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

    // Set the pen with the brush and the width
    pen.setBrush(brush);
    pen.setWidth(5);
    setPen(pen);


    /*setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton); */
    
    // Creating the timer so it can run in other thread.
    QTimer * timer = new QTimer();

    // Setting up the thread so it runs the move method.
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));

    // Starting up the timer with 60 miliseconds.
    timer->start(speed);
}

// Build the heart
/**
 * Function go to the top left
 */
void Ball::goDiagnollyTopLeft(){
    setPos(x()-2,y()-2);
    if( (int) x() == -100 && (int) y() == -100){
        this->isGoingTopLeft = false;
        this->isGoingMiddleLeft = true;
    }
    
}

/**
 * Function go to the middle left
 */ 
void Ball::goDiagnollyMiddleLeft(){
    setPos(x()-2,y()+2);
    if(x() == -200 && y() == 0){
        this->isGoingMiddleLeft = false;
        this->isGoingBottomMiddle = true;
    }
}

/**
 * Function go to the bottom middle
 */
void Ball::goDiagnollyBottomMiddle(){
    setPos(x()+2,y()+2);
    if(x() == 0 && y() == 200){
        this->isGoingBottomMiddle = false;
        this->isGoingMiddleRight = true;
    }
}

/**
 * Function go to the middle right
 */
void Ball::goDiagnollyMiddleRight(){
    setPos(x()+2,y()-2);
    if(x() == 200 && y() == 0){
        this->isGoingMiddleRight = false;
        this->isGoingTopRight = true;
    }
}

/**
 * Function go to the top right
 */
void Ball::goDiagnollyTopRight(){
    setPos(x()-2,y()-2);
    if(x() == 100 && y() == -100){
        this->isGoingTopRight = false;
        this->isGoingMiddleCenter = true;
    }
}

/**
 * Function go to the start
 */
void Ball::goDiagnollyMiddleCenter(){
    setPos(x()-2,y()+2);
    if(x() == 0 && y() == 0){
        this->isGoingMiddleCenter = false;
        // End game
        this->endedPath = true;
    }
}

void Ball::move(){
    // Move the ball
    // X: 0 - X: 600
    // Y: 0 - Y: 400

    // Start at                                                    //    | x: 600/2  | y: 400/2

    // This is the path that the ball is going to make
    // Ball only can run if the game is running
    if ( this->isRunning ) {
        if ( this->isGoingTopLeft  ) { this->goDiagnollyTopLeft(); }
        if ( this->isGoingMiddleLeft ) { this->goDiagnollyMiddleLeft(); }
        if ( this->isGoingBottomMiddle ) { this->goDiagnollyBottomMiddle(); }
        if ( this->isGoingMiddleRight ) { this->goDiagnollyMiddleRight(); }
        if ( this->isGoingTopRight ) { this->goDiagnollyTopRight(); }
        if ( this->isGoingMiddleCenter ) { this->goDiagnollyMiddleCenter(); }
    }

}
