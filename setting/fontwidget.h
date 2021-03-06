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

#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>

class SessionDispatcher;
class MainWindow;
class QLabel;
class QPushButton;
class QComboBox;
class QDoubleSpinBox;

class FontWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FontWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, MainWindow *window = 0);
    ~FontWidget();
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void setDefaultFont();
    void setDesktopFont();
    void setMonospaceFont();
    void setDocumentFont();
    void setTitlebarFont();
    void setScalingValue(double value);
    void setFontHinting(QString selected);
    void setFontAntialiasing(QString selected);
    void resetDefaultFont(QString cur_font);
    void resetDesktopFont(QString cur_font);
    void resetMonospaceFont(QString cur_font);
    void resetDocumentFont(QString cur_font);
    void resetTitlebarFont(QString cur_font);

private:
    SessionDispatcher *sessionproxy;
    MainWindow *parentWindow;
    QLabel *default_font_label;
    QLabel *desktop_font_label;
    QLabel *monospace_font_label;
    QLabel *document_font_label;
    QLabel *titlebar_font_label;
    QLabel *scaling_label;
    QLabel *hinting_label;
    QLabel *antialiasing_label;
    QPushButton *default_font_btn;
    QPushButton *desktop_font_btn;
    QPushButton *monospace_font_btn;
    QPushButton *document_font_btn;
    QPushButton *titlebar_font_btn;
    QDoubleSpinBox *scaling_slider;
    QComboBox *hinting_combo;
    QComboBox *antialiasing_combo;

    QString current_font;
    QString desktop_font;
    QString monospace_font;
    QString document_font;
    QString titlebar_font;
};

#endif // FONTWIDGET_H
