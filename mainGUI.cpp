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
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class Window : public QWidget {
 public:
    Window(EventManager::EventManager *eventManager, const std::string& profileFile);

 private:
    void startShocker();

    void stopShocker();

    void createSystemTray();

    void generateDMenu();

    QAction *quitAction{};
    QAction *startAction{};
    QAction *stopAction{};
    QAction *showAction{};
    QSystemTrayIcon *trayIcon{};
    QMenu *trayIconMenu{};
    QLineEdit * profileEdit{};
    EventManager::EventManager *eventManager{};
    std::thread *_thread{};
    std::string profileFile;


};

Window::Window(EventManager::EventManager *eventManager, const std::string& profileFile) :
        trayIcon(new QSystemTrayIcon(this)),
        trayIconMenu(new QMenu(this)),
        eventManager(eventManager),
        profileFile(profileFile){
    createSystemTray();
    generateDMenu();
    startShocker();
}

void Window::startShocker() {
    _thread = new std::thread(
            &EventManager::EventManager::start,
            this->eventManager);
    _thread->detach();
    trayIconMenu->insertAction(startAction, stopAction);
    trayIconMenu->removeAction(startAction);
}

void Window::stopShocker() {
    eventManager->stop();
    trayIconMenu->insertAction(stopAction, startAction);
    trayIconMenu->removeAction(stopAction);
}

void Window::createSystemTray() {
    QIcon icon(tr("/usr/share/icons/shocker_icon.png"));
    setWindowIcon(icon);

    startAction = new QAction(tr("&Start"), this);
    stopAction = new QAction(tr("&Stop"), this);
    quitAction = new QAction(tr("&Quit"), this);
    showAction = new QAction(tr("&Show Window"), this);

    connect(startAction, &QAction::triggered, this, &Window::startShocker);
    connect(stopAction, &QAction::triggered, this, &Window::stopShocker);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(showAction, &QAction::triggered, this, &Window::show);

    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(icon);
    trayIcon->show();
    trayIconMenu->addAction(startAction);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void Window::generateDMenu() {
    auto * vbox = new QHBoxLayout();
    auto * hbox = new QVBoxLayout();
    profileEdit = new QLineEdit(profileFile.c_str());
    auto *loadButton =  new QPushButton("Load Profile");
    vbox->addWidget(profileEdit);
    vbox->addSpacing(10);
    vbox->addWidget(loadButton);
    hbox->addItem(vbox);
    setLayout(hbox);
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
        auto keybinding = JsonMapper::createMapping(profileFile, configPath);
        Controller::ControllerInputReader controllerInputReader(joystickDeviceFile);
        EventConverter eventConverter(keybinding);
        EventManager::EventManager eventManager(controllerInputReader,
                                                eventConverter,
                                                keybinding);


        Window window(&eventManager, profileFile);

        window.resize(500, 150);
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
