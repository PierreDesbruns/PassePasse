// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCompleter>
#include <QString>
#include <QDebug>

#include "loginwindow.h"
#include "entry.h"
#include "entrylistview.h"
#include "entrylistdelegate.h"
#include "entrylistmodel.h"
#include "entryview.h"
#include "entrymanager.h"
#include "searchbar.h"
#include "searchmodel.h"


namespace pwm {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    // Entry manager
    EntryManager* entryManager;

    // Main widget
    QWidget* mainContent;
    QHBoxLayout* mainLayout;

    // Left widget
    QWidget* leftWidget;
    QVBoxLayout* leftLayout;
    // Search bar
    SearchBar* searchBar;
    QCompleter* searchCompleter;
    SearchModel* searchModel;
    // Entry list view
    EntryListView* entryListView;
    EntryListModel* entryListModel;
    // Add button
    QPushButton* addEntryButton;

    // Right widget
    QWidget* rightWidget;
    QVBoxLayout* rightLayout;
    // Entry view widget
    EntryView* entryView;
    // Delete button
    QPushButton* delEntryButton;

    // Login window
    LoginWindow *loginWindow; // window responsible for authentification. Shows only on start.
};

} // namespace pwm

#endif // MAINWINDOW_H
