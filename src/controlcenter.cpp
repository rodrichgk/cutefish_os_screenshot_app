#include "controlcenter.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QPixmap>
#include <QStandardPaths>
#include <QDateTime>
#include "screenshotview.h"
#include <QTimer>
controlCenter::controlCenter(QQuickView *parent) : QQuickView(parent)
{
    rootContext()->setContextProperty("view", this);
    setFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    setScreen(qGuiApp->primaryScreen());
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QUrl("qrc:/qml/main.qml"));
    setGeometry(screen()->geometry());
    setColor(QColor(0, 0, 0, 220));
}

void controlCenter::start()
{
    //QPixmap p = qGuiApp->primaryScreen()->grabWindow(0);
    //p.save("/tmp/cutefish-screenshot.png");

    setVisible(true);
    setKeyboardGrabEnabled(true);
}

void controlCenter::quit()
{
    qGuiApp->quit();
}

void controlCenter::changeScreen(int screenIndex)
{
    setVisible(false);
    QCoreApplication::processEvents();
    QTimer::singleShot(200, [screenIndex]() {
        ScreenshotView *m_screenshotview = new ScreenshotView(nullptr, qGuiApp->screens().at(screenIndex));
        m_screenshotview->start(qGuiApp->screens().at(screenIndex));
    });
}

QStringList controlCenter::getScreenNames()
{
    screens = qGuiApp->screens();
    for(QScreen* screen : screens)
    {
        screenNames.append(screen->name());
    }
    return screenNames;
}
