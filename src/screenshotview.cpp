/*
 * Copyright (C) 2021 CutefishOS Team.
 *
 * Author:     Reion Wong <reionwong@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "screenshotview.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QScreen>
#include <QPixmap>
#include <QStandardPaths>
#include <QDateTime>

ScreenshotView::ScreenshotView(QQuickView *parent)
    : QQuickView(parent)
{
    // 保存图片
    QPixmap p = qGuiApp->primaryScreen()->grabWindow(0);
    p.save("/tmp/cutefish-screenshot.png");

    rootContext()->setContextProperty("view", this);

    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QUrl("qrc:/qml/main.qml"));
    showFullScreen();
}

void ScreenshotView::quit()
{
    qGuiApp->quit();
}

void ScreenshotView::saveFile(QRect rect)
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fileName = QString("%1/Screenshot_%2.png")
                              .arg(desktopPath)
                              .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));

    QImage image("/tmp/cutefish-screenshot.png");
    QImage cropped = image.copy(rect);
    cropped.save(fileName);

    this->quit();
}