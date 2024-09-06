#include "ControlGroupObserver.h"
#include <QGraphicsScene>

namespace ADEV {
// ControlGroupObserver
ControlGroupObserver::ControlGroupObserver(ItemShaper *itemShaper)
    : m_itemShaper(itemShaper)
{}

ControlGroupObserver::~ControlGroupObserver()
{}

void ControlGroupObserver::setControlGroup(ControlPointGroup *controlGroup)
{
    m_controlGroup = controlGroup;
    connect(m_controlGroup, &ControlPointGroup::rectInfo,
            this, &ControlGroupObserver::formItem);
}

ItemShaper* ControlGroupObserver::itemShaper() const
{
    return m_itemShaper;
}

void ControlGroupObserver::handleControlPointDestroy()
{
    if (m_controlGroup)
        delete m_controlGroup;
    emit destroy();
}
// end of ControlGroupObserver
// ----------------------------------------------------------------------
// ControlRectangleObserver
ControlRectangleObserver::ControlRectangleObserver(ItemShaper* itemShaper)
    : ControlGroupObserver(itemShaper)
{
}

void ControlRectangleObserver::formItem(QRectF rect, qreal angle)
{
    Q_UNUSED(angle);
    qreal w = itemShaper()->strokeWidth();
    QPainterPath left   = itemShaper()->lineToStroke(QLineF(rect.bottomLeft(), rect.topLeft()), w);
    QPainterPath top    = itemShaper()->lineToStroke(QLineF(rect.topRight(), rect.topLeft()), w);
    QPainterPath right  = itemShaper()->lineToStroke(QLineF(rect.topRight(), rect.bottomRight()), w);
    QPainterPath bottom = itemShaper()->lineToStroke(QLineF(rect.bottomLeft(), rect.bottomRight()), w);
    QPainterPath ret;
    ret = ret.united(left);
    ret = ret.united(top);
    ret = ret.united(right);
    ret = ret.united(bottom);
    itemShaper()->setStrokePath(ret);
}
// end of ControlRectangleObserver
// ----------------------------------------------------------------------


} // end of namespace ADEV
