#include "WhiteBoard.h"
#include "ItemLayer/ControlPointGroup.h"
#include "ItemLayer/BaseGraphicsItem.h"
#include "ItemLayer/ControlGroupObserver.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    using namespace ADEV;
    QApplication a(argc, argv);
    EightWayMovementGroup eightWayMovement(QRectF(QPointF(100, 100), QPointF(200, 200)));
    BaseGraphicsItem baseItem(10, QBrush(Qt::red));
    ControlRectangleObserver rectangleObserver(&baseItem);
    rectangleObserver.formItem(eightWayMovement.mapRectToScene(eightWayMovement.boundingRect()), 0.0);
    rectangleObserver.setControlGroup(&eightWayMovement);
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1024, 512);
    scene.addItem(&baseItem);
    scene.addItem(&eightWayMovement);
    QGraphicsView view(&scene);
    view.show();
    return a.exec();
}
