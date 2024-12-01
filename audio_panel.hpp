/**
 * @file audio_panel.hpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 11/11/2024
 */

#ifndef SOUND_DECK_AUDIO_PANEL_HPP
#define SOUND_DECK_AUDIO_PANEL_HPP

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class AudioPanel;
}
QT_END_NAMESPACE

class AudioPanel : public QWidget
{
Q_OBJECT

public:
    explicit AudioPanel(QWidget *parent = nullptr);

    ~AudioPanel() override;

    bool is_playing();
    bool has_loaded_media();

public slots:
    void select_file();
    void toggle_play();
    void play();
    void pause();
    void stop();
    void toggle_repeat();

private slots:
    void set_volume(int value);
    void update_duration(qint64 duration);
    void update_position(qint64 position);
    void set_position(int position);
    void update_status(QMediaPlayer::MediaStatus status);
    void update_ticker();
    void load_file(const QString &file_path);

private:
    Ui::AudioPanel *ui;
    QMediaPlayer *player;
    QAudioOutput *audio_output;
    QString ticker_text = "";
    int ticker_position = 0, track_duration = 0;
    bool loaded_media = false, playing = false, repeat_mode = false;
};


#endif //SOUND_DECK_AUDIO_PANEL_HPP
