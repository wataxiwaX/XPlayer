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
    connect(controller, &Controller::positionChange, player, &QMediaPlayer::setPosition);
    connect(player, &QMediaPlayer::positionChanged, controller, &Controller::setPosition);
    connect(player, &QMediaPlayer::durationChanged, controller, &Controller::setDuration);
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
