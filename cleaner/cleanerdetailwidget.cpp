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

#include "cleanerdetailwidget.h"
#include "ui_cleanerdetailwidget.h"
#include "../mainui/mainwindow.h"
#include "../component/cleansubgroup.h"
#include <QDebug>
#include <QBoxLayout>

CleanerDetailWidget::CleanerDetailWidget(QWidget *parent, SessionDispatcher *seroxy, SystemDispatcher *syproxy, MainWindow *window, Toolkits *kits)
    : QWidget(parent), sessionproxy(seroxy), systemproxy(syproxy), parentWindow(window), toolKits(kits),
    ui(new Ui::CleanerDetailWidget)
{
    ui->setupUi(this);
    this->setFixedSize(900, 403);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");
//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, QBrush(Qt::white));
//    this->setPalette(palette);

    ui->scrollArea->setFixedSize(900, 403);
    ui->scrollArea->setAutoFillBackground(true);
    ui->scrollArea->setBackgroundRole(QPalette::Light);

    colorFlag = false;

    grid_layout = new QGridLayout();
    rowIndex = columnIndex = 0;

    cache_apt_items = NULL;
    cache_apt_btn = NULL;
    cache_software_items = NULL;
    cache_software_btn = NULL;
    cache_thumbnails_items = NULL;
    cache_thumbnails_btn = NULL;
    cache_firefox_items = NULL;
    cache_firefox_btn = NULL;
    cache_chromium_items = NULL;
    cache_chromium_btn = NULL;

    package_unneed_items = NULL;
    package_unneed_btn = NULL;
    package_oldkernel_items = NULL;
    package_oldkernel_btn = NULL;
    package_configfile_items = NULL;
    package_configfile_btn = NULL;

    cookies_firefox_items = NULL;
    cookies_firefox_btn = NULL;
    cookies_chromium_items = NULL;
    cookies_chromium_btn = NULL;

    trace_firefox_btn = NULL;
    trace_chromium_btn = NULL;
    trace_system_btn = NULL;

    appendNum1 = 0;
    appendNum2 = 0;
    appendNum3 = 0;

    ui->scrollAreaWidgetContents->setLayout(grid_layout);
    this->setLanguage();
}

CleanerDetailWidget::~CleanerDetailWidget()
{
    if(grid_layout != NULL)
    {
        delete grid_layout;
        grid_layout = NULL;
    }
    delete ui;
}

void CleanerDetailWidget::CleanUIAndData()
{
    rowIndex = columnIndex = 0;
    appendNum1 = 0;
    appendNum2 = 0;
    appendNum3 = 0;
    cache_apt_list.clear();
    cache_software_list.clear();
    cache_thumbnails_list.clear();
    cache_firefox_list.clear();
    cache_chromium_list.clear();
    package_unneed_list.clear();
    package_oldkernel_list.clear();
    package_configfile_list.clear();
    cookies_firefox_list.clear();
    cookies_chromium_list.clear();
    trace_firefox_count.clear();
    trace_chromium_count.clear();
    trace_system_count.clear();

    //clear ui
    while(grid_layout != NULL && grid_layout->count() > 0)
    {
        QWidget* widget = grid_layout->itemAt(0)->widget();
        grid_layout->removeWidget(widget);
        delete widget;
    }
}

void CleanerDetailWidget::showReciveData(const QStringList &data)
{
    //----------------------------------------------------------------Cache---------------------------
    if(data.at(0) == "Belong:Cache.apt" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            cache_apt_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.software-center" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            cache_software_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.thumbnails" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            cache_thumbnails_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            cache_firefox_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            cache_chromium_list.append(data.at(1).split(":").at(1));
        }
    }
    //----------------------------------------------------------------Package---------------------------
    else if(data.at(0) == "Belong:Packages.unneed" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            package_unneed_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Packages.oldkernel" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            package_oldkernel_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Packages.configfile" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            package_configfile_list.append(data.at(1).split(":").at(1));
        }
    }

    //----------------------------------------------------------------Cookies---------------------------
    else if(data.at(0) == "Belong:Cookies.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
        {
            cookies_firefox_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cookies.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
        {
            cookies_chromium_list.append(data.at(1).split(":").at(1));
        }
    }

    //----------------------------------------------------------------History Trace---------------------------
    else if(data.at(0) == "Belong:History.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0)
                trace_firefox_count = data.at(1).split(":").at(1);
        }
    }
    else if(data.at(0) == "Belong:History.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0)
                trace_chromium_count = data.at(1).split(":").at(1);
        }
    }
    else if(data.at(0) == "Belong:History.system" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0)
                trace_system_count = data.at(1).split(":").at(1);
        }
    }
}

void CleanerDetailWidget::showReciveStatus(const QString &status)
{
    if(status == "Complete:Cache")
    {
        if(cache_apt_list.length() > 0)
        {
            cache_apt_items = new CleanListWidget(cache_apt_list, tr("Apt Cache Clean Items"));
//            cache_apt_btn = new CommonCheckBox(0, "://res/cache");
            cache_apt_btn = new CleanSubGroup(0, "://res/item");
//            cache_apt_btn->setFixedSize(160, 130);
//            cache_apt_btn->setFixedSize(160, 200);
            cache_apt_btn->setStatusTip("cache-apt");
            cache_apt_btn->setLabelText(tr("Apt Cache count:"), cache_apt_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_apt_items, SIGNAL(notifyMainCheckBox(int)), cache_apt_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，显示自定义页面
            connect(cache_apt_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_apt_btn, SIGNAL(spreadStatus(int)), cache_apt_items, SLOT(resetSubCheckbox(int)));
//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cache_apt_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cache_apt_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cache_apt_btn);
//                    appendNum3 += 1;
//                }
//            }
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cache_apt_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cache_apt_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }

        }
        if(cache_software_list.length() > 0)
        {
            cache_software_items = new CleanListWidget(cache_software_list, tr("Software Cache Clean Items"));
//            cache_software_btn = new CommonCheckBox(0, "://res/cache");
            cache_software_btn = new CleanSubGroup(0, "://res/item");
//            cache_software_btn->setFixedSize(160, 130);
//            cache_software_btn->setFixedSize(160, 200);
            cache_software_btn->setStatusTip("cache-software");
            cache_software_btn->setLabelText(tr("Software Cache count:"), cache_software_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_software_items, SIGNAL(notifyMainCheckBox(int)), cache_software_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_software_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_software_btn, SIGNAL(spreadStatus(int)), cache_software_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cache_software_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cache_software_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cache_software_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cache_software_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cache_software_btn);
//                    appendNum3 += 1;
//                }
//            }

        }
        if(cache_thumbnails_list.length() > 0)
        {
            cache_thumbnails_items = new CleanListWidget(cache_thumbnails_list, tr("Thumbnails Cache Clean Items"));
//            cache_thumbnails_btn = new CommonCheckBox(0, "://res/cache");
            cache_thumbnails_btn = new CleanSubGroup(0, "://res/item");
//            cache_thumbnails_btn->setFixedSize(160, 130);
//            cache_thumbnails_btn->setFixedSize(160, 200);
            cache_thumbnails_btn->setStatusTip("cache-thumbnails");
            cache_thumbnails_btn->setLabelText(tr("Thumbnails Cache Count:"), cache_thumbnails_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_thumbnails_items, SIGNAL(notifyMainCheckBox(int)), cache_thumbnails_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_thumbnails_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_thumbnails_btn, SIGNAL(spreadStatus(int)), cache_thumbnails_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cache_thumbnails_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cache_thumbnails_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cache_thumbnails_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cache_thumbnails_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cache_thumbnails_btn);
//                    appendNum3 += 1;
//                }
//            }
        }


        if(cache_firefox_list.length() > 0)
        {
            cache_firefox_items = new CleanListWidget(cache_firefox_list, tr("Software Cache Clean Items"));
//            cache_firefox_btn = new CommonCheckBox(0, "://res/cache");
            cache_firefox_btn = new CleanSubGroup(0, "://res/item");
//            cache_firefox_btn->setFixedSize(160, 130);
            cache_firefox_btn->setStatusTip("cache-firefox");
            cache_firefox_btn->setLabelText(tr("Firefox Cache Count:"), cache_firefox_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_firefox_items, SIGNAL(notifyMainCheckBox(int)), cache_firefox_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_firefox_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_firefox_btn, SIGNAL(spreadStatus(int)), cache_firefox_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cache_firefox_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cache_firefox_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cache_firefox_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cache_firefox_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cache_firefox_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
        if(cache_chromium_list.length() > 0)
        {
            cache_chromium_items = new CleanListWidget(cache_chromium_list, tr("Thumbnails Cache Clean Items"));
//            cache_chromium_btn = new CommonCheckBox(0, "://res/cache");
            cache_chromium_btn = new CleanSubGroup(0, "://res/item");
//            cache_chromium_btn->setFixedSize(160, 130);
            cache_chromium_btn->setStatusTip("cache-chromium");
            cache_chromium_btn->setLabelText(tr("Chromium Cache Count:"), cache_chromium_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_chromium_items, SIGNAL(notifyMainCheckBox(int)), cache_chromium_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_chromium_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_chromium_btn, SIGNAL(spreadStatus(int)), cache_chromium_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cache_chromium_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cache_chromium_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }

//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cache_chromium_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cache_chromium_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cache_chromium_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
    }
    else if(status == "Complete:Cookies")
    {
//        doing_label->setText(tr("Cookies Scan OK......"));
        if(cookies_firefox_list.length() > 0)
        {
            cookies_firefox_items = new CleanListWidget(cookies_firefox_list, tr("Thumbnails Cache Clean Items"));
//            cookies_firefox_btn = new CommonCheckBox(0, "://res/cookie");
            cookies_firefox_btn = new CleanSubGroup(0, "://res/item");
//            cookies_firefox_btn->setFixedSize(160, 130);
            cookies_firefox_btn->setStatusTip("cookes-firefox");
            cookies_firefox_btn->setLabelText(tr("Firefox Cookies Count:"), cookies_firefox_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cookies_firefox_items, SIGNAL(notifyMainCheckBox(int)), cookies_firefox_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_firefox_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_firefox_btn, SIGNAL(spreadStatus(int)), cookies_firefox_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cookies_firefox_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cookies_firefox_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }

//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cookies_firefox_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cookies_firefox_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cookies_firefox_btn);
//                    appendNum3 += 1;
//                }
//            }

        }
        if(cookies_chromium_list.length() > 0)
        {
            cookies_chromium_items = new CleanListWidget(cookies_chromium_list, tr("Thumbnails Cache Clean Items"));
//            cookies_chromium_btn = new CommonCheckBox(0, "://res/cache");
            cookies_chromium_btn = new CleanSubGroup(0, "://res/item");
//            cookies_chromium_btn->setFixedSize(160, 130);
            cookies_chromium_btn->setStatusTip("cookes-chromium");
            cookies_chromium_btn->setLabelText(tr("Chromium Cookies Count:"), cookies_chromium_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cookies_chromium_items, SIGNAL(notifyMainCheckBox(int)), cookies_chromium_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_chromium_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_chromium_btn, SIGNAL(spreadStatus(int)), cookies_chromium_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(cookies_chromium_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(cookies_chromium_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }


//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(cookies_chromium_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(cookies_chromium_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(cookies_chromium_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
    }
    else if(status == "Complete:History")
    {
//        doing_label->setText(tr("History Scan OK......"));
        if(trace_firefox_count.length() > 0)
        {
//            trace_firefox_btn = new CommonCheckBox(0, "://res/cache");
            trace_firefox_btn = new CleanSubGroup(0, "://res/item");
//            trace_firefox_btn->setFixedSize(160, 130);
            trace_firefox_btn->hideCustomButton();
            trace_firefox_btn->setStatusTip("history-firefox");
            trace_firefox_btn->setLabelText(tr("Firefox History Count:"), trace_firefox_count.toInt());
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(trace_firefox_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(trace_firefox_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(trace_firefox_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(trace_firefox_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(trace_firefox_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
        if(trace_chromium_count.length() > 0)
        {
            trace_chromium_btn = new CleanSubGroup(0, "://res/item");
            trace_chromium_btn->hideCustomButton();
            trace_chromium_btn->setStatusTip("history-chromium");
            trace_chromium_btn->setLabelText(tr("Chromium History Count:"), trace_chromium_count.toInt());
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(trace_chromium_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(trace_chromium_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
        }

        if(trace_system_count.length() > 0)
        {
            trace_system_btn = new CleanSubGroup(0, "://res/item");
            trace_system_btn->hideCustomButton();
            trace_system_btn->setStatusTip("history-system");
            trace_system_btn->setLabelText(tr("System History Count:"), trace_system_count.toInt());
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(trace_system_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(trace_system_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
        }
    }
    else if(status == "Complete:Packages")
    {
//        doing_label->setText(tr("Packages Scan OK......"));
        if(package_unneed_list.length() > 0)
        {
            package_unneed_items = new CleanListWidget(package_unneed_list, tr("Thumbnails Cache Clean Items"));
//            package_unneed_btn = new CommonCheckBox(0, "://res/cache");
            package_unneed_btn = new CleanSubGroup(0, "://res/item");
//            package_unneed_btn->setFixedSize(160, 130);
            package_unneed_btn->setStatusTip("package-unneed");
            package_unneed_btn->setLabelText(tr("Package Unneed Count:"),package_unneed_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(package_unneed_items, SIGNAL(notifyMainCheckBox(int)), package_unneed_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_unneed_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_unneed_btn, SIGNAL(spreadStatus(int)), package_unneed_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(package_unneed_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(package_unneed_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }

//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(package_unneed_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(package_unneed_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(package_unneed_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
        if(package_oldkernel_list.length() > 0)
        {
            package_oldkernel_items = new CleanListWidget(package_oldkernel_list, tr("Thumbnails Cache Clean Items"));
//            package_oldkernel_btn = new CommonCheckBox(0, "://res/cache");
            package_oldkernel_btn = new CleanSubGroup(0, "://res/item");
//            package_oldkernel_btn->setFixedSize(160, 130);
            package_oldkernel_btn->setStatusTip("package-oldkernel");
            package_oldkernel_btn->setLabelText(tr("Package oldkernel Count:"), package_oldkernel_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(package_oldkernel_items, SIGNAL(notifyMainCheckBox(int)), package_oldkernel_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_oldkernel_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_oldkernel_btn, SIGNAL(spreadStatus(int)), package_oldkernel_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(package_oldkernel_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(package_oldkernel_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }

//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(package_oldkernel_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(package_oldkernel_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(package_oldkernel_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
        if(package_configfile_list.length() > 0)
        {
            package_configfile_items = new CleanListWidget(package_configfile_list, tr("Thumbnails Cache Clean Items"));
//            package_configfile_btn = new CommonCheckBox(0, "://res/cache");
            package_configfile_btn = new CleanSubGroup(0, "://res/item");
//            package_configfile_btn->setFixedSize(160, 130);
            package_configfile_btn->setStatusTip("package-configfile");
            package_configfile_btn->setLabelText(tr("Package configfile Count:"),package_configfile_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(package_configfile_items, SIGNAL(notifyMainCheckBox(int)), package_configfile_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_configfile_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_configfile_btn, SIGNAL(spreadStatus(int)), package_configfile_items, SLOT(resetSubCheckbox(int)));
            if(grid_layout == NULL)
            {
                grid_layout = new QGridLayout();
            }
            if(columnIndex < 5)
            {
                grid_layout->addWidget(package_configfile_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
            else {
                rowIndex += 1;
                columnIndex = 0;
                grid_layout->addWidget(package_configfile_btn, rowIndex, columnIndex);
                columnIndex += 1;
            }
//            if(appendNum1 < 4)
//            {
//                layout1->addWidget(package_configfile_btn);
//                appendNum1 += 1;
//            }
//            else
//            {
//                if(appendNum2 < 4)
//                {
//                    layout2->addWidget(package_configfile_btn);
//                    appendNum2 += 1;
//                }
//                else
//                {
//                    layout3->addWidget(package_configfile_btn);
//                    appendNum3 += 1;
//                }
//            }
        }
    }
    else if(status == "Complete:All")
    {
//        QBoxLayout *main_layout = new QBoxLayout(QBoxLayout::LeftToRight);
//        if(cache_apt_btn != NULL)
//            main_layout->addWidget(cache_apt_btn);
//        if(cache_software_btn != NULL)
//            main_layout->addWidget(cache_software_btn);
//        if(cache_thumbnails_btn != NULL)
//            main_layout->addWidget(cache_thumbnails_btn);
//        if(cache_firefox_btn != NULL)
//             main_layout->addWidget(cache_firefox_btn);
//         if(cache_chromium_btn != NULL)
//             main_layout->addWidget(cache_chromium_btn);
//         if(cookies_firefox_btn != NULL)
//              main_layout->addWidget(cookies_firefox_btn);
//          if(cookies_chromium_btn != NULL)
//              main_layout->addWidget(cookies_chromium_btn);
//          if(package_unneed_btn != NULL)
//              main_layout->addWidget(package_unneed_btn);
//          if(package_oldkernel_btn != NULL)
//               main_layout->addWidget(package_oldkernel_btn);
//           if(package_configfile_btn != NULL)
//               main_layout->addWidget(package_configfile_btn);
//        main_layout->setSpacing(30);
//        main_layout->setMargin(0);
//        main_layout->setContentsMargins(0,0,0,0);
//        setLayout(main_layout);
    }
}

void CleanerDetailWidget::showCustomPage()
{
    QObject *object = QObject::sender();
//    CommonCheckBox *checkbox = qobject_cast<CommonCheckBox *>(object);
    CleanSubGroup *checkbox = qobject_cast<CleanSubGroup *>(object);
    QString object_name = checkbox->statusTip();
    if(object_name == "cache-apt")
    {
//        if(cache_apt_items != NULL)
//        {
        if(cache_apt_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cache_apt_items->move(w_x, w_y);
            cache_apt_items->show();
        }
        else
        {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
    else if(object_name == "cache-software")
    {
        if(cache_software_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cache_software_items->move(w_x, w_y);
            cache_software_items->show();
        }
        else
        {
            cache_software_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
    else if(object_name == "cache-thumbnails")
    {
        if(cache_thumbnails_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cache_thumbnails_items->move(w_x, w_y);
            cache_thumbnails_items->show();
        }
        else
        {
            cache_thumbnails_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }



    else if(object_name == "cache-firefox")
    {
        if(cache_firefox_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cache_firefox_items->move(w_x, w_y);
            cache_firefox_items->show();
        }
        else
        {
            cache_firefox_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }

    else if(object_name == "cache-chromium")
    {
        if(cache_chromium_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cache_chromium_items->move(w_x, w_y);
            cache_chromium_items->show();
        }
        else
        {
            cache_chromium_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
    else if(object_name == "cookes-firefox")
    {
        if(cookies_firefox_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cookies_firefox_items->move(w_x, w_y);
            cookies_firefox_items->show();
        }
        else
        {
            cookies_firefox_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
    else if(object_name == "cookes-chromium")
    {
        if(cookies_chromium_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cookies_chromium_items->move(w_x, w_y);
            cookies_chromium_items->show();
        }
        else
        {
            cookies_chromium_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }


    else if(object_name == "package-unneed")
    {
        if(package_unneed_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            package_unneed_items->move(w_x, w_y);
            package_unneed_items->show();
        }
        else
        {
            package_unneed_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
    else if(object_name == "package-oldkernel")
    {
        if(package_oldkernel_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            package_oldkernel_items->move(w_x, w_y);
            package_oldkernel_items->show();
        }
        else
        {
            package_oldkernel_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
    else if(object_name == "package-configfile")
    {
        if(package_configfile_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            package_configfile_items->move(w_x, w_y);
            package_configfile_items->show();
        }
        else
        {
            package_configfile_items->hide();
        }
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
    }
    else if(object_name == "history-firefox" || object_name == "history-chromium") {
        if(cache_apt_items != NULL && !cache_apt_items->isHidden()) {
            cache_apt_items->hide();
        }
        if(cache_software_items != NULL && !cache_software_items->isHidden()) {
            cache_software_items->hide();
        }
        if(cache_thumbnails_items != NULL && !cache_thumbnails_items->isHidden()) {
            cache_thumbnails_items->hide();
        }
        if(cache_firefox_items != NULL && !cache_firefox_items->isHidden()) {
            cache_firefox_items->hide();
        }
        if(cache_chromium_items != NULL && !cache_chromium_items->isHidden()) {
            cache_chromium_items->hide();
        }
        if(cookies_firefox_items != NULL && !cookies_firefox_items->isHidden()) {
            cookies_firefox_items->hide();
        }
        if(cookies_chromium_items != NULL && !cookies_chromium_items->isHidden()) {
            cookies_chromium_items->hide();
        }
        if(package_unneed_items != NULL && !package_unneed_items->isHidden()) {
            package_unneed_items->hide();
        }
        if(package_oldkernel_items != NULL && !package_oldkernel_items->isHidden()) {
            package_oldkernel_items->hide();
        }
        if(package_configfile_items != NULL && !package_configfile_items->isHidden()) {
            package_configfile_items->hide();
        }
    }
}

void CleanerDetailWidget::setLanguage()
{
//    title_label->setText(tr("Cleaning up the system cache"));
//    description_label->setText(tr("Deep cleaning up the system cache, to save disk space"));
}

void CleanerDetailWidget::receiveCleanSignal()
{
    this->getAllSelectedItems();
    if(argsData.empty())
    {
        toolKits->alertMSG(parentWindow->geometry().topLeft().x(), parentWindow->geometry().topLeft().y(), tr("Clean args is empty!"));
    }
    else
    {
//        qDebug() << "args is.........." << argsData;
        systemproxy->set_user_homedir_qt();
        systemproxy->cleanAllSelectItems(argsData);
    }
}

//void CleanerDetailWidget::receivePolicyKitSignal(bool status)
//{
//    //status = true:ok
//    //status = false:cacel
//    if(status)//ok
//    {
//        emit this->showActionAnimaiton();
//    }
//}

void CleanerDetailWidget::getAllSelectedItems()
{
    argsData.clear();
    QStringList fileTmp;
    QStringList packageTmp;
    QStringList firefoxcookieTmp;
    QStringList chromiumcookieTmp;

    if(cache_apt_btn != NULL && cache_apt_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cache_apt_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            fileTmp.append(tmp.at(i));
        }
    }
    if(cache_software_btn != NULL && cache_software_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cache_software_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            fileTmp.append(tmp.at(i));
        }
    }
    if(cache_thumbnails_btn != NULL && cache_thumbnails_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cache_thumbnails_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            fileTmp.append(tmp.at(i));
        }
    }
    if(cache_firefox_btn != NULL && cache_firefox_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cache_firefox_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            fileTmp.append(tmp.at(i));
        }
    }
    if(cache_chromium_btn != NULL && cache_chromium_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cache_chromium_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            fileTmp.append(tmp.at(i));
        }
    }
    if(package_unneed_btn != NULL && package_unneed_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_unneed_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }
    if(package_oldkernel_btn != NULL && package_oldkernel_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_oldkernel_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }
    if(package_configfile_btn != NULL && package_configfile_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_configfile_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }
    if(cookies_firefox_btn != NULL && cookies_firefox_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cookies_firefox_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            firefoxcookieTmp.append(tmp.at(i));
        }
    }
    if(cookies_chromium_btn != NULL && cookies_chromium_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cookies_chromium_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            chromiumcookieTmp.append(tmp.at(i));
        }
    }
    if(trace_firefox_btn != NULL && trace_firefox_btn->getCheckBoxStatus() != 0)
    {
        argsData.insert("firefox-history", QStringList() << trace_firefox_count);
    }
    if(trace_chromium_btn != NULL && trace_chromium_btn->getCheckBoxStatus() != 0)
    {
       argsData.insert("chromium-history", QStringList() << trace_chromium_count);
    }
    if(trace_system_btn != NULL && trace_system_btn->getCheckBoxStatus() != 0)
    {
       argsData.insert("system-history", QStringList() << trace_system_count);
    }

    if(fileTmp.length() > 0)
        argsData.insert("file", fileTmp);
    if(packageTmp.length() > 0)
        argsData.insert("package", packageTmp);
    if(firefoxcookieTmp.length() > 0)
        argsData.insert("firefox-cookie", firefoxcookieTmp);
    if(chromiumcookieTmp.length() > 0)
        argsData.insert("chromium-cookie", chromiumcookieTmp);
}
