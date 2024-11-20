/**
 * @file main_window.hpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 11/11/2024
 */

#ifndef SOUND_DECK_MAIN_WINDOW_HPP
#define SOUND_DECK_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QGridLayout>
#include "audio_panel.hpp"
#include "control_panel.hpp"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void control_play();
    void control_pause();
    void control_stop();

private:
    Ui::MainWindow *ui;
    QGridLayout *layout;
    AudioPanel *panel1, *panel2, *panel3, *panel4;
    ControlPanel *control_panel;
};


#endif //SOUND_DECK_MAIN_WINDOW_HPP
