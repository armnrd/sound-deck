#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QDial>
#include <QSlider>
#include <QUrl>
#include <QLabel>
#include <QStyle>
#include <QDir>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QGridLayout>
#include <QTimer>

class AudioPanel : public QWidget {
    Q_OBJECT

public:
    AudioPanel(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        QHBoxLayout *dialsLayout = new QHBoxLayout();
        QHBoxLayout *buttonsLayout = new QHBoxLayout();
        QHBoxLayout *volumeLayout = new QHBoxLayout();

        // Create controls
        selectButton = new QPushButton(this);
        playButton = new QPushButton(this);
        pauseButton = new QPushButton(this);
        stopButton = new QPushButton(this);
        repeatButton = new QPushButton(this);
        statusLabel = new QLabel("No file selected", this);
        volumeSlider = new QSlider(Qt::Horizontal, this);
        volumeSlider->setRange(0, 100);
        volumeSlider->setValue(50);
        seekDial = new QDial(this);
        seekDial->setRange(0, 100);

        // Set button icons
        selectButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        repeatButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

        // Arrange widgets
        dialsLayout->addWidget(seekDial);
        buttonsLayout->addWidget(selectButton);
        selectButton->setMaximumWidth(30);
        buttonsLayout->setSpacing(5);
        buttonsLayout->addWidget(playButton);
        playButton->setMaximumWidth(30);
        buttonsLayout->setSpacing(5);
        buttonsLayout->addWidget(pauseButton);
        pauseButton->setMaximumWidth(30);
        buttonsLayout->setSpacing(5);
        buttonsLayout->addWidget(stopButton);
        stopButton->setMaximumWidth(30);
        buttonsLayout->setSpacing(5);
        buttonsLayout->addWidget(repeatButton);
        repeatButton->setMaximumWidth(30);
        buttonsLayout->setSpacing(5);

        volumeLayout->addWidget(volumeSlider);
        volumeSlider->setFixedWidth(buttonsLayout->sizeHint().width());

        // Add layouts to main layout
        mainLayout->addLayout(dialsLayout);
        mainLayout->addLayout(buttonsLayout);
        mainLayout->addLayout(volumeLayout);
        mainLayout->addWidget(statusLabel);

        // Initialize media player
        player = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.5);

        // Connect signals and slots
        connect(selectButton, &QPushButton::clicked, this, &AudioPanel::selectFile);
        connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
        connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
        connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
        connect(repeatButton, &QPushButton::clicked, this, &AudioPanel::toggleRepeat);
        connect(volumeSlider, &QSlider::valueChanged, this, &AudioPanel::setVolume);
        connect(player, &QMediaPlayer::durationChanged, this, &AudioPanel::updateDuration);
        connect(player, &QMediaPlayer::positionChanged, this, &AudioPanel::updatePosition);
        connect(seekDial, &QDial::sliderMoved, this, &AudioPanel::setPosition);
        connect(player, &QMediaPlayer::mediaStatusChanged, this, &AudioPanel::updateStatus);

        tickerTimer = new QTimer(this);
        connect(tickerTimer, &QTimer::timeout, this, &AudioPanel::updateTicker);
        tickerTimer->start(100);
    }

private slots:
    void selectFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Audio File", "", "Audio Files (*.mp3 *.m4a)");
        if (!fileName.isEmpty()) {
            player->setSource(QUrl::fromLocalFile(fileName));
            statusLabel->setText(fileName);
            selectedFileName = fileName;
            tickerPosition = 0;
        }
    }

    void toggleRepeat() {
        if (repeatMode) {
            repeatMode = false;
            repeatButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
            player->setLoops(QMediaPlayer::Infinite); // No repeat
        } else {
            repeatMode = true;
            repeatButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
            player->setLoops(1); // Repeat
        }
    }

    void setVolume(int value) {
        audioOutput->setVolume(value / 100.0);
    }

    void updateDuration(qint64 duration) {
        seekDial->setMaximum(static_cast<int>(duration));
    }

    void updatePosition(qint64 position) {
        seekDial->setValue(static_cast<int>(position));
    }

    void setPosition(int position) {
        player->setPosition(position);
    }

    void updateStatus(QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::LoadedMedia) {
            playButton->setEnabled(true);
            pauseButton->setEnabled(true);
            stopButton->setEnabled(true);
        }
    }

    void updateTicker() {
        if (!selectedFileName.isEmpty()) {
            QString tickerText = selectedFileName.mid(tickerPosition) + " " + selectedFileName.left(tickerPosition);
            seekDial->setToolTip(tickerText);
            tickerPosition = (tickerPosition + 1) % selectedFileName.length();
        }
    }

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QPushButton *selectButton;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *repeatButton;
    QLabel *statusLabel;
    QSlider *volumeSlider;
    QDial *seekDial;
    QTimer *tickerTimer;
    QString selectedFileName;
    int tickerPosition = 0;
    bool repeatMode = false;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Audio Player with Multiple Panels");
    mainWindow.resize(800, 600);

    QGridLayout *layout = new QGridLayout(&mainWindow);

    AudioPanel *panel1 = new AudioPanel(&mainWindow);
    AudioPanel *panel2 = new AudioPanel(&mainWindow);
    AudioPanel *panel3 = new AudioPanel(&mainWindow);
    AudioPanel *panel4 = new AudioPanel(&mainWindow);

    layout->addWidget(panel1, 0, 0);
    layout->addWidget(panel2, 0, 1);
    layout->addWidget(panel3, 1, 0);
    layout->addWidget(panel4, 1, 1);

    mainWindow.setLayout(layout);
    mainWindow.show();

    return app.exec();
}

#include "main_test.moc"
