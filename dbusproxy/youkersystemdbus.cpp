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

#include "youkersystemdbus.h"
#include <QDebug>
#include <QMap>

SystemDispatcher::SystemDispatcher(QObject *parent)
//    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin.youker",
                               "/",
                               "com.ubuntukylin.youker",
                               QDBusConnection::systemBus());
    thread = new KThread(this);
    QObject::connect(systemiface,SIGNAL(quit_clean(bool)),this,SLOT(handler_interrupt_clean(bool)));
    QObject::connect(systemiface,SIGNAL(clean_complete_onekey(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_onekey(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(status_for_quick_clean(QString,QString)),this,SLOT(handler_status_for_quick_clean(QString,QString)));

    QObject::connect(systemiface,SIGNAL(subpage_data_signal(QStringList)),this,SLOT(handlerCleanerSubPageDataSignal(QStringList)));
    QObject::connect(systemiface,SIGNAL(subpage_status_signal(QString, QString)),this,SLOT(handlerCleanerSubPageStatusSignal(QString, QString)));
    QObject::connect(systemiface,SIGNAL(subpage_error_signal(QString)),this,SLOT(handlerCleanerSubPageErrorSignal(QString)));
}

SystemDispatcher::~SystemDispatcher() {
    if(thread != NULL) {
        delete thread;
        thread = NULL;
    }
    this->exit_qt();
    if (systemiface != NULL) {
        delete systemiface;
        systemiface = NULL;
    }
}

void SystemDispatcher::cleanAllSelectItems(QMap<QString, QVariant> selectMap)
{
    QStringList tmp;
    thread->initValues(selectMap, tmp, systemiface, "remove_select_items");
    thread->start();
}

//void SystemDispatcher::kill_root_process_qt(QString pid) {
//    systemiface->call("kill_root_process", pid);
//}

bool SystemDispatcher::set_cursor_theme_with_root_qt(QString theme) {
    QDBusReply<bool> reply = systemiface->call("set_cursor_theme_with_root", theme);
    return reply.value();
}

QMap<QString, QVariant> SystemDispatcher::get_computer_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_computer_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get computer info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_cpu_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_cpu_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get cpu info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_memory_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_memory_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get memory info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_board_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_board_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get board info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_harddisk_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_harddisk_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get harddisk info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_networkcard_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_networkcard_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get networkcard info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_monitor_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_monitor_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get monitor info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_cdrom_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_cdrom_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get cdrom info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QMap<QString, QVariant> SystemDispatcher::get_audiocard_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_audiocard_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
    }
    else {
        qDebug() << "get audiocard info failed!";
        QMap<QString, QVariant> value;
        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

QString SystemDispatcher::get_time_value_qt() {
    QDBusReply<QString> reply = systemiface->call("get_time_value");
    return reply.value();
}

void SystemDispatcher::exit_qt() {
    systemiface->call("exit");
}

QString SystemDispatcher::get_system_daemon_qt() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

//void SystemDispatcher::set_homedir_qt() {
//    QString homedir = QDir::homePath();
//    systemiface->call("set_homedir", homedir);
//}

void SystemDispatcher::set_user_homedir_qt() {
    QString homedir = QDir::homePath();
    systemiface->call("set_user_homedir", homedir);
}

void SystemDispatcher::handler_interrupt_clean(bool status) {
    emit policykitCleanSignal(status);
}

void SystemDispatcher::handler_clear_rubbish_main_onekey(QString msg) {
     emit finishCleanWorkMain(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_error(QString msg) {
     emit finishCleanWorkMainError(msg);
}

void SystemDispatcher::handler_status_for_quick_clean(QString type, QString status) {
    emit quickCleanProcess(type, status);
}

//-----------------------sound------------------------
QStringList SystemDispatcher::get_sound_themes_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_sound_themes");
    return reply.value();
}

void SystemDispatcher::handlerCleanerSubPageDataSignal(QStringList data)
{
    emit this->tellCleanerMainData(data);
}

void SystemDispatcher::handlerCleanerSubPageStatusSignal(QString status, QString domain)
{
    if(status == "Complete:All" && domain == "finish")
    {
        emit sendCleanOverSignal();
    }
    else {
        emit this->tellCleanerMainStatus(status, domain);
    }
}

void SystemDispatcher::handlerCleanerSubPageErrorSignal(QString status)
{
    emit sendCleanErrorSignal(status);
}

//QStringList SystemDispatcher::get_sounds_qt() {
//    QDBusReply<QStringList> reply = systemiface->call("get_sounds");
//    return reply.value();
//}

//void SystemDispatcher::replace_sound_file_qt(QString origfile, QString targetfile) {
//    systemiface->call("replace_sound_file", origfile, targetfile);
//}
//void SystemDispatcher::restore_sound_file_qt(QString targetfile) {
//    systemiface->call("restore_sound_file", targetfile);
//}

//void SystemDispatcher::restore_all_sound_file_qt(QString soundtheme) {
//    systemiface->call("restore_all_sound_file", soundtheme);
//}

//-----------------------others------------------------
void SystemDispatcher::custom_plymouth_bg_qt(QString plymouthName) {
    systemiface->call("custom_plymouth_bg", plymouthName);
}

void SystemDispatcher::add_new_plymouth_qt(QString customBG, QString plymouthName) {
    systemiface->call("add_new_plymouth", customBG, plymouthName);
}

QStringList SystemDispatcher::get_existing_plymouth_list_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_existing_plymouth_list");
    return reply.value();
}

void SystemDispatcher::plymouth_init_check_qt() {
    systemiface->call("plymouth_init_check");
}

QString SystemDispatcher::get_image_path_qt(QString name) {
    QDBusReply<QString> reply = systemiface->call("get_image_path", name);
    return reply.value();
}

QString SystemDispatcher::delete_plymouth_qt(QString plymouthName) {
    QDBusReply<QString> reply = systemiface->call("delete_plymouth", plymouthName);
    return reply.value();
}

void SystemDispatcher::clean_by_main_one_key_qt() {
    QStringList argList;
    argList << "1" << "1" << "1";
    QMap<QString, QVariant> data;
    thread->initValues(data, argList, systemiface, "onekey_clean_crufts_function");
    thread->start();
}
