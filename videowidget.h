#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>

//视频播放部件
class VideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0)
        : QVideoWidget(parent){ setAcceptDrops(true); }
    ~VideoWidget() {}

public slots:
    void fullScreen();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event); //双击事件
    void mouseReleaseEvent(QMouseEvent *event);     //鼠标松开事件
    void keyReleaseEvent(QKeyEvent *event);         //键盘松开事件
    void dragEnterEvent(QDragEnterEvent *event);    //拖 事件
    void dropEvent(QDropEvent *event);              //放 事件

signals:
    void playChanged();                             //播放状态改变信号
    void volumeChanged(int value);                  //音量改变信号
    void positionChanged(qint64 value);             //进度改变信号
    void sendFile(QString filename);                //视频拖放信号
};

#endif // VIDEOWIDGET_H
