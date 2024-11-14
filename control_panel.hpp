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

private:
    Ui::ControlPanel *ui;
};


#endif //SOUND_DECK_CONTROL_PANEL_HPP
