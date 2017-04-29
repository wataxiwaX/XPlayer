/****************
播放器下方的控制条
*****************/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlayer>
#include <QKeyEvent>

class Controller : public QHBoxLayout
{
    Q_OBJECT

public:
    Controller(QWidget *parent = 0);
    ~Controller();

public slots:
    void stateChanged(QMediaPlayer::State state);   //播放状态发生改变
    void setPosition(qint64 value);                 //当前播放进度
    void setDuration(qint64 value);                 //时长
    void setVolume(int value);                      //设置音量

private slots:
    void playClicked();                             //“播放/暂停”按钮按下时触发
    void volumeSlided();                            //滑动音量条时触发
    void fullClicked();                             //按下全屏按钮触发
    void positionSlided();                          //滑动进度条是触发

signals:
    void playChanged();                             //“播放/暂停”信号
    void volumeChanged(int value);                  //音量条滑动信号
    void fullChanged();                             //全屏信号
    void positionChange(int value);                 //进度条滑动信号

private:
    void updateDurationInfo(qint64 value);          //更新视频时长
    void updateCurrentInfo(qint64 value);           //更新进度

    QLabel *position_label;                 //显示当前时间的标签
    QSlider *duration_slider;               //进度条
    QLabel *duration_label;                 //显示视频时长的标签
    QPushButton *back_button;                //“上一个”按钮
    QPushButton *play_button;                //“播放/暂停”按钮
    QPushButton *next_button;                //“下一个”按钮
    QSlider *volume_slider;                 //音量条
    QPushButton *full_button;                //全屏按钮
};

#endif // CONTROLLER_H
