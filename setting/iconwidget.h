/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"

class SessionDispatcher;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QComboBox;

class IconWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IconWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~IconWidget();
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void changeSwitcherStatus();
    void setIconTheme(QString selectTheme);
    void setShowDesktopIcons();
    void setFolderIcon();
    void setNetworkIcon();
    void setRecycleBinIcon();
    void setDiskIcon();

private:
    SessionDispatcher *sessionproxy;

    QLabel *theme_label;
    QLabel *show_label;
    QLabel *folder_label;
    QLabel *network_label;
    QLabel *recycle_label;
    QLabel *disk_label;
    QComboBox *theme_combo;
    KylinSwitcher *show_switcher;
    KylinSwitcher *folder_switcher;
    KylinSwitcher *network_switcher;
    KylinSwitcher *recycle_switcher;
    KylinSwitcher *disk_switcher;
};

#endif // ICONWIDGET_H
