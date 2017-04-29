#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "videowidget.h"
#include "controller.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QMediaPlayer>

//控制条和视频播放部件的父部件
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
    void setVolume(int value);                              //设置音量
    void setPosition(qint64 value);                         //设置进度

protected:
    void keyReleaseEvent(QKeyEvent *event);

private:
    QVBoxLayout *main_layout;                               //布局器
    VideoWidget *video_widget;
    QMediaPlayer *player;
    Controller *controller;                                 //控制条
};

#endif // PLAYERWIDGET_H
