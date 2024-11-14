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
}

ControlPanel::~ControlPanel()
{
    delete ui;
}
