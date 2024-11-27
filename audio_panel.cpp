/**
 * @file audio_panel.cpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 11/11/2024
 */

#include <QPushButton>
#include <QSlider>
#include <QStyle>
#include <QDial>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
#include "audio_panel.hpp"
#include "ui_audio_panel.h"


AudioPanel::AudioPanel(QWidget *parent) :
        QWidget(parent), ui(new Ui::AudioPanel)
{
    ui->setupUi(this);

    // Initialize member variables
    player = new QMediaPlayer(this);
    audio_output = new QAudioOutput(this);
    ticker_timer = new QTimer(this);

    // Connect signals and slots using UI elements
    connect(ui->dial_seek, &QDial::sliderMoved, this, &AudioPanel::set_position);
    connect(ui->button_select, &QPushButton::clicked, this, &AudioPanel::select_file);
    connect(ui->button_toggle_play, &QPushButton::clicked, this, &AudioPanel::toggle_play);
    connect(ui->button_stop, &QPushButton::clicked, this, &AudioPanel::stop);
    connect(ui->button_repeat, &QPushButton::clicked, this, &AudioPanel::toggle_repeat);
    connect(ui->slider_volume, &QSlider::valueChanged, this, &AudioPanel::set_volume);
    connect(player, &QMediaPlayer::durationChanged, this, &AudioPanel::update_duration);
    connect(player, &QMediaPlayer::positionChanged, this, &AudioPanel::update_position);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &AudioPanel::update_status);
    connect(ticker_timer, &QTimer::timeout, this, &AudioPanel::update_ticker);

    // Set up media player and ticker
    player->setAudioOutput(audio_output);
    ticker_timer->start(100);
    ui->slider_volume->setValue(100);

    // Set button icons
    ui->button_select->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_toggle_play->setEnabled(false);
    ui->button_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->button_stop->setEnabled(false);
    ui->button_repeat->setIcon(style()->standardIcon(QStyle::SP_CommandLink));
    ui->button_repeat->setEnabled(false);
}

AudioPanel::~AudioPanel()
{
    delete ui;
}

bool AudioPanel::is_playing()
{
    return playing;
}

bool AudioPanel::has_loaded_media()
{
    return loaded_media;
}

void AudioPanel::select_file()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Open Audio File", "", "Audio Files (*.mp3 *.m4a *.ogg)");
    if (!file_path.isEmpty()) {
        stop();
        player->setSource(QUrl::fromLocalFile(file_path));
        QFileInfo file_info(file_path);
        ticker_text = file_info.fileName() + "    ";
        ticker_position = 0;
    }
}

void AudioPanel::toggle_play()
{
    if (playing) {
        player->pause();
        ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playing = false;
    } else {
        player->play();
        ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playing = true;
    }
}

void AudioPanel::play()
{
    if (!playing && loaded_media) {
        player->play();
        ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playing = true;
    }
}

void AudioPanel::pause()
{
    if (playing) {
        player->pause();
        ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playing = false;
    }
}

void AudioPanel::stop()
{
    if (playing) {
        player->stop();
        ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playing = false;
    }
}

void AudioPanel::toggle_repeat()
{
    if (repeat_mode) {
        repeat_mode = false;
        ui->button_repeat->setIcon(style()->standardIcon(QStyle::SP_CommandLink));
//        player->setLoops(1); // No repeat
    } else {
        repeat_mode = true;
        ui->button_repeat->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
//        player->setLoops(QMediaPlayer::Infinite); // Repeat
    }
}

void AudioPanel::set_volume(int value)
{
    audio_output->setVolume(value / 100.0);
}

void AudioPanel::update_duration(qint64 duration)
{
    this->duration = static_cast<int>(duration);
    ui->dial_seek->setMaximum(static_cast<int>(duration));
}

void AudioPanel::update_position(qint64 position)
{
    ui->dial_seek->setValue(static_cast<int>(position) % duration);
}

void AudioPanel::set_position(int position)
{
    player->setPosition(position);
}

void AudioPanel::update_status(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        ui->button_toggle_play->setEnabled(true);
        ui->button_stop->setEnabled(true);
        ui->button_repeat->setEnabled(true);
        loaded_media = true;
    } else if (status == QMediaPlayer::EndOfMedia) { // media repeat logic
        if (repeat_mode) {
            player->play();
        } else {
            ui->button_toggle_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            playing = false;
        }
    }
}

void AudioPanel::update_ticker()
{
    if (!ticker_text.isEmpty()) {
        QString ticker_text_section = ticker_text.mid(ticker_position) + "     " + ticker_text.left(ticker_position);
        ticker_text_section = ticker_text_section.first(ticker_length - 2) + "  "; // use first ticker_length - 2 chars
        ticker_text_section = ticker_text_section.leftJustified(ticker_length, ' '); // pad to ticker_length chars
        ui->label_ticker->setText(ticker_text_section);
        ticker_position = (ticker_position + 1) % ticker_text.length();
    }
}
