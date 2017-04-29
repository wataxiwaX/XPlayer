#include "videowidget.h"

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        fullScreen();
}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit playChanged();
}

void VideoWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Space:
        emit playChanged();
        break;
    case Qt::Key_Escape:
        setFullScreen(false);
        break;
    case Qt::Key_Right:
        emit positionChanged(qint64(15000));
        break;
    case Qt::Key_Left:
        emit positionChanged(qint64(-10000));
        break;
    case Qt::Key_Up:
        emit volumeChanged(5);
        break;
    case Qt::Key_Down:
        emit volumeChanged(-5);
        break;
    default:
        break;
    }
}

void VideoWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void VideoWidget::dropEvent(QDropEvent *event)
{
    emit sendFile(event->mimeData()->text().remove(QRegExp("[\r\n].")));

    event->acceptProposedAction();
}

void VideoWidget::fullScreen()
{
    switch (isFullScreen()) {
    case true:
        setFullScreen(false);
        break;
    default:
        setFullScreen(true);
        break;
    }
}
