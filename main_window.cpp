/**
 * @file main_window.cpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 11/11/2024
 */

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include <QGridLayout>
#include <QDebug>
#include "main_window.hpp"
#include "ui_main_window.h"
#include "audio_panel.hpp"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize member variables
    layout = new QGridLayout(this);
    panel1 = new AudioPanel(this);
    panel2 = new AudioPanel(this);
    panel3 = new AudioPanel(this);
    panel4 = new AudioPanel(this);

    // Set layout
    layout->addWidget(panel1, 0, 0);
    layout->addWidget(panel2, 0, 1);
    layout->addWidget(panel3, 1, 0);
    layout->addWidget(panel4, 1, 1);
    adjustSize();
//    ui->centralwidget->adjustSize();
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
