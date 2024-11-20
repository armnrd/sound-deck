/**
 * @file control_panel.hpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 14/11/2024
 */

#ifndef SOUND_DECK_CONTROL_PANEL_HPP
#define SOUND_DECK_CONTROL_PANEL_HPP

#include <QWidget>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class ControlPanel;
}
QT_END_NAMESPACE

class ControlPanel : public QWidget
{
Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);

    ~ControlPanel() override;

    QPushButton *get_button_play();

    QPushButton *get_button_pause();

    QPushButton *get_button_stop();

private:
    Ui::ControlPanel *ui;
};


#endif //SOUND_DECK_CONTROL_PANEL_HPP
