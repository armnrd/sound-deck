/**
 * @file main_window.cpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 11/11/2024
 */

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include <QGridLayout>
#include <QStyle>
#include <QDebug>
#include "main_window.hpp"
#include "ui_main_window.h"
#include "audio_panel.hpp"
#include "control_panel.hpp"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize member variables
    layout = new QGridLayout(nullptr);
    panel1 = new AudioPanel(this);
    panel2 = new AudioPanel(this);
    panel3 = new AudioPanel(this);
    panel4 = new AudioPanel(this);
    control_panel = new ControlPanel(this);

    // Connect signals from control_panel
    connect(control_panel->get_button_toggle_play(), &QPushButton::clicked, this, &MainWindow::control_toggle_play);
    connect(control_panel->get_button_stop(), &QPushButton::clicked, this, &MainWindow::control_stop);

    // Set layout
    layout->addWidget(panel1, 0, 0);
    layout->addWidget(panel2, 0, 1);
    layout->addWidget(panel3, 1, 0);
    layout->addWidget(panel4, 1, 1);
    layout->addWidget(control_panel, 2, 0, 1, 2);
    adjustSize();
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::control_toggle_play()
{
    bool playing = false;
    for (auto &panel: {panel1, panel2, panel3, panel4}) {
        if (panel->is_playing()) {
            playing = true;
        }
    }
    if (playing) {
        for (auto &panel: {panel1, panel2, panel3, panel4}) {
            panel->pause();
        }
        control_panel->get_button_toggle_play()->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    } else {
        for (auto &panel: {panel1, panel2, panel3, panel4}) {
            if (panel->has_loaded_media()) {
                panel->play();
                control_panel->get_button_toggle_play()->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            }
        }
    }
}

void MainWindow::control_stop()
{
    for (auto &panel: {panel1, panel2, panel3, panel4}) {
        panel->stop();
    }
    control_panel->get_button_toggle_play()->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}
