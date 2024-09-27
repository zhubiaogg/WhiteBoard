#include "BackgroundItem.h"

#include <QGraphicsScene>
#include <QPainter>

namespace ADEV
{
// BackgroundItem
BackgroundItem::BackgroundItem(QColor color, const QSizeF& size, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_size(size)
    , m_color(color)
{
    setZValue(-1); // 背景的Z值，需要Scene保证该值为Item中最小的Z值
}

QSizeF BackgroundItem::size() const
{
    return m_size;
}

QColor BackgroundItem::color() const
{
    return m_color;
}

void BackgroundItem::setColor(QColor color)
{
    m_color = color;
    emit colorChanged(m_color);
}

void BackgroundItem::resize(QSizeF size)
{
    m_size = size;
}

QRectF BackgroundItem::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void BackgroundItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // 什么都不画且背景颜色为白色的BackgroundItem就是一张纯粹的白板
}

QVariant BackgroundItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSceneHasChanged)
    {
        QGraphicsScene* scene = value.value<QGraphicsScene*>();
        if (scene != nullptr)
        {
            QBrush brush(m_color);
            brush.setStyle(Qt::SolidPattern);
            scene->setBackgroundBrush(brush);
            scene->setSceneRect(boundingRect());
            setPos(0, 0);
            connect(this, &BackgroundItem::colorChanged, this, &BackgroundItem::changeSceneBackgroundColor);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void BackgroundItem::changeSceneBackgroundColor(QColor color)
{
    QBrush brush(color);
    brush.setStyle(Qt::SolidPattern);
    scene()->setBackgroundBrush(brush);
}
// end of BackgroundItem

// BackgroundImageItem
BackgroundImageItem::BackgroundImageItem(const QImage& image, const QSizeF& imageSize)
    : BackgroundItem(Qt::white, imageSize)
    , m_image(image)
{
}

void BackgroundImageItem::resize(QSizeF size)
{
    BackgroundItem::resize(size);
}

void BackgroundImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage drawImg = m_image.scaled(size().toSize(), Qt::KeepAspectRatio);
    painter->drawImage(QPointF(0, 0), drawImg);
}
// end of BackgroundImageItem

// BackgroundPathItem
BackgroundPathItem::BackgroundPathItem(const QPainterPath& path, QGraphicsItem* parent)
    : BackgroundItem(Qt::white, path.boundingRect().size(), parent)
    , m_path(path)
{
}

void BackgroundPathItem::resize(QSizeF size)
{
    BackgroundItem::resize(size);
}

void BackgroundPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    QPixmap pix(boundingRect().size().toSize());
    QPainter pter(&pix);
    pter.setPen(pen);
    pter.drawPath(m_path);
    pter.end();
    pix = pix.scaled(size().toSize(), Qt::KeepAspectRatio);
    painter->drawPixmap(QPointF(0,0), pix);
}
// end of BackgroundPathItem
} // end of namespace ADEV
