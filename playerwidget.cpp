#include "playerwidget.h"

#include <QState>
#include <QFileDialog>
#include <QMimeData>

PlayerWidget::PlayerWidget(QWidget *parent)
    : QWidget(parent)
{
    main_layout = new QVBoxLayout(this);
    video_widget = new VideoWidget(this);
    player = new QMediaPlayer(this);
    controller = new Controller(this);

    player->setVideoOutput(video_widget);
    player->setVolume(50);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);

    main_layout->addWidget(video_widget);
    main_layout->addLayout(controller);
    setLayout(main_layout);


    video_widget->show();

    connect(controller, &Controller::playChanged, this, &PlayerWidget::play);
    connect(controller, &Controller::volumeChanged, player, &QMediaPlayer::setVolume);
    connect(controller, &Controller::fullChanged, video_widget, &VideoWidget::fullScreen);
    connect(player, &QMediaPlayer::stateChanged, controller, &Controller::stateChanged);
    connect(video_widget, &VideoWidget::playChanged, this, &PlayerWidget::play);
    connect(video_widget, &VideoWidget::sendFile, this, &PlayerWidget::receiveFile);
    connect(video_widget, &VideoWidget::volumeChanged, this, &PlayerWidget::setVolume);
    connect(video_widget, &VideoWidget::positionChanged, this, &PlayerWidget::setPosition);
    connect(controller, &Controller::positionChange, player, &QMediaPlayer::setPosition);
    connect(player, &QMediaPlayer::positionChanged, controller, &Controller::setPosition);
    connect(player, &QMediaPlayer::durationChanged, controller, &Controller::setDuration);
    connect(player,&QMediaPlayer::volumeChanged, controller, &Controller::setVolume);
}

PlayerWidget::~PlayerWidget()
{
}

void PlayerWidget::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), QDir::homePath(), \
                                                    tr("Video Files (*.mp4 *.flv *.mkv\
                                                                     *.avi *.rmvb *.3gp);;\
                                                        All Files (*.*)"));
    if(!filename.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(filename));
        player->play();
    }
}

void PlayerWidget::play()
{
    switch(player->state()) {
    case QMediaPlayer::PlayingState:
        player->pause();
        break;
    case QMediaPlayer::PausedState:
        player->play();
        break;
    default:
        break;
    }
}

void PlayerWidget::receiveFile(QString filename)
{
    if(!filename.isEmpty()) {
        player->setMedia(QUrl(filename));
        player->play();
        controller->setDuration(player->duration());
    }
}

void PlayerWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Space:
        play();
        break;
    case Qt::Key_Right:
        setPosition(qint64(15000));
        break;
    case Qt::Key_Left:
        setPosition(qint64(-10000));
        break;
    case Qt::Key_Up:
        setVolume(5);
        break;
    case Qt::Key_Down:
        setVolume(-5);
        break;
    default:
        break;
    }
}

void PlayerWidget::setVolume(int value)
{
    player->setVolume(player->volume() + value);
}

void PlayerWidget::setPosition(qint64 value)
{
    player->setPosition(player->position() + value);
}

