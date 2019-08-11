#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QPen>


/**
 * Class Ball
 * For creating a ball and moving it synchronously
 */
class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    // Constructor
    Ball(int id, int x, int y, bool & isRunning);
    bool endedPath = false;

public slots:
    void move();

private:
    // Variables
    bool isGoingTopLeft = true, isGoingMiddleLeft = false, isGoingBottomMiddle = false, 
    isGoingMiddleRight = false, isGoingTopRight = false, isGoingMiddleCenter = false;
    int id;
    QPen pen;
    int speed = 60;
    bool & isRunning;

    // Methods
    void goDiagnollyTopLeft();
    void goDiagnollyMiddleLeft();
    void goDiagnollyBottomMiddle();
    void goDiagnollyMiddleRight();
    void goDiagnollyTopRight();
    void goDiagnollyMiddleCenter();
};

#endif // BALL_H
