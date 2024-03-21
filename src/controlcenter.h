#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <QObject>
#include <QQuickView>
#include <QScreen>

class controlCenter : public QQuickView
{
    Q_OBJECT
public:
    explicit controlCenter(QQuickView * parent = nullptr);

    void start();

    Q_INVOKABLE void quit();
    Q_INVOKABLE QStringList getScreenNames();
    Q_INVOKABLE void changeScreen(int screenIndex);

    void removeTmpFile();
signals:
    void aboutToClose(int screenIndex);

private:
    QList<QScreen*> screens;
    QStringList screenNames;
    void setScreenList();
    bool m_visibility = true;
};

#endif // CONTROLCENTER_H
