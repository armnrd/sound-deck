#include <QApplication>
#include <QGridLayout>
#include "audio_panel.hpp"
#include "main_window.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
