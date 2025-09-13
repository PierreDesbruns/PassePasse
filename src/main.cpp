// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include <QApplication>
#include <stdio.h>
#include <stdlib.h>

#include "mainwindow.h"


QtMessageHandler originalHandler = nullptr;

void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message = qFormatLogMessage(type, context, msg);
    static FILE * f = fopen("log.txt", "a");
    fprintf(f, "%s\n", qPrintable(message));
    fflush(f);
}

int main(int argc, char *argv[])
{
    if (sodium_init() == -1) return 1;
    originalHandler = qInstallMessageHandler(logToFile);
    qSetMessagePattern("[%{time yyyy.MM.dd hh:mm:ss}] %{type}: %{message}");
    QApplication a(argc, argv);
    pwm::MainWindow w;
    w.show();
    return a.exec();
}
