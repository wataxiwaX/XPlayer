#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "controller.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

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
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void playChanged();                             //播放状态改变信号
    void sendFile(QString filename);                //视频拖放信号
};

//播放器主要部件，包含控制条和视频播放部件
class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();

    qint64 videoDuration() { return player->duration(); }   //获取视频时长

public slots:
    void openFile();                                        //按下open菜单时触发
    void play();                                            //按下“播放/暂停”按钮时触发
    void receiveFile(QString filename);                     //文件拖放是触发

private:
    QVBoxLayout *main_layout;                               //布局器
    VideoWidget *video_widget;
    QMediaPlayer *player;
    Controller *controller;                                 //控制条
};

#endif // PLAYERWIDGET_H
