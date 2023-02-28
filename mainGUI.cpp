//  Copyright (c)  2022.  Raphael Prandini Thomé de Abrantes
//  Use of this source code is governed by an MIT-style
//  license that can be found in the LICENSE file or at
//  https://opensource.org/licenses/MIT.
#include <QApplication>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QMenu>
#include <JsonMapper.h>
#include <ControllerInputReader.h>
#include <EventManager.h>
#include <Exception.h>
#include <QMessageBox>
#include <thread>


class Window : public QWidget {
public:
    explicit Window(EventManager::EventManager *eventManager);

private:
    void startShocker();

    void stopShocker();

    void gracefullyShutdown();

    QAction *quitAction;
    QAction *startAction;
    QAction *stopAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    EventManager::EventManager *eventManager;
};

Window::Window(EventManager::EventManager *eventManager) {
    this->eventManager = eventManager;
    QIcon icon(tr("/usr/share/icons/shocker_icon.png"));
    trayIconMenu = new QMenu(this);

    startAction = new QAction(tr("&Start"), this);
    stopAction = new QAction(tr("&Stop"), this);
    quitAction = new QAction(tr("&Quit"), this);

    connect(startAction, &QAction::triggered, this, &Window::startShocker);
    connect(stopAction, &QAction::triggered, this, &Window::stopShocker);
    connect(quitAction, &QAction::triggered, this, &Window::gracefullyShutdown);
    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
        switch (reason) {
            case QSystemTrayIcon::Unknown:
            case QSystemTrayIcon::Context:
            case QSystemTrayIcon::DoubleClick:
            case QSystemTrayIcon::MiddleClick:
                break;
            case QSystemTrayIcon::Trigger:
                trayIconMenu->popup(QCursor::pos());

        }
    });
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->show();
    startShocker();
}

void Window::startShocker() {
    std::thread thread1(&EventManager::EventManager::start, eventManager);
    thread1.detach();
    trayIconMenu->removeAction(startAction);
    trayIconMenu->removeAction(quitAction);
    trayIconMenu->addAction(stopAction);
    trayIconMenu->addAction(quitAction);
}

void Window::stopShocker() {
    eventManager->stop();
    trayIconMenu->removeAction(stopAction);
    trayIconMenu->removeAction(quitAction);
    trayIconMenu->addAction(startAction);
    trayIconMenu->addAction(quitAction);
}

void Window::gracefullyShutdown() {
    eventManager->stop();
    qApp->quit();
}

int main(int argc, char *argv[]) {
    std::string joystickDeviceFile("/dev/input/js0");
    const std::string configPath = getenv("HOME") +
                                   std::string("/.config/shocker/");

    std::string profileFile(configPath + "profiles/default.json");
    if (argc < 1) {
        profileFile.assign(argv[1]);
    }

    QApplication app(argc, argv);
    try {
        auto controller = JsonMapper::createMapping(profileFile, configPath);
        Controller::ControllerInputReader controllerInputReader(joystickDeviceFile);
        EventConverter eventConverter(controller);
        EventManager::EventManager eventManager(controllerInputReader,
                                                eventConverter);
        Window window(&eventManager);

        window.resize(250, 150);
        window.setWindowTitle("ShockerGUI");
        window.hide();
        return app.exec();
    } catch (std::exception &e) {
        QMessageBox::critical(nullptr, QObject::tr("ShockerGUI"),
                              QObject::tr("ShockerGUI failed with this "
                                          "exception:\n\n") + e.what());
        return 1;
    }
}
