#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget* parent)
{
    this->setParent(parent);
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    emit mouseClicked(event->position().x(), event->position().y());
}

void MyGraphicsView::resizeEvent(QResizeEvent* event)
{
    emit resized();
}
