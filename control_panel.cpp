/**
 * @file control_panel.cpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 14/11/2024
 */

// You may need to build the project (run Qt uic code generator) to get "ui_control_panel.h" resolved

#include "control_panel.hpp"
#include "ui_control_panel.h"


ControlPanel::ControlPanel(QWidget *parent) :
        QWidget(parent), ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    // Set button icons
    ui->button_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->button_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->button_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

QPushButton *ControlPanel::get_button_play() {
    return ui->button_play;
}

QPushButton *ControlPanel::get_button_pause() {
    return ui->button_pause;
}

QPushButton *ControlPanel::get_button_stop() {
    return ui->button_stop;
}
