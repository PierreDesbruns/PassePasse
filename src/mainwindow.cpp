// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "mainwindow.h"

namespace pwm {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setMinimumSize(750, 550);
    setWindowTitle("PassePasse");
    setWindowIcon(QIcon(":/logo"));

    // Entry manager
    entryManager = new EntryManager(this);

    // Search bar
    searchModel = new SearchModel(entryManager);
    searchCompleter = new QCompleter();
    searchCompleter->setModel(searchModel);
    searchCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    searchCompleter->setCompletionMode(QCompleter::PopupCompletion);
    searchCompleter->setFilterMode(Qt::MatchContains);
    searchBar = new SearchBar();
    searchBar->setCompleter(searchCompleter);
    searchBar->setClearButtonEnabled(true);

    // Login window
    loginWindow = new LoginWindow(this);
    loginWindow->setModal(Qt::ApplicationModal);

    // Buttons
    addEntryButton = new QPushButton(QString("+"));
    delEntryButton = new QPushButton(QString("-"));

    // Entry list view
    entryListModel = new EntryListModel(this);
    entryListView = new EntryListView();
    entryListView->setModel(entryListModel);
    entryListView->setItemDelegate(new EntryListDelegate(entryListView));

    // Left widget
    leftWidget = new QWidget();
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    leftWidget->setFixedWidth(350);
    leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(searchBar);
    leftLayout->addWidget(entryListView);
    leftLayout->addWidget(addEntryButton);

    // Entry information group
    entryView = new EntryView(entryManager);
    entryView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Right widget
    rightWidget = new QWidget();
    rightWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(entryView, 1);
    rightLayout->addWidget(delEntryButton, 1);

    // Main widget
    mainContent = new QWidget();
    mainLayout = new QHBoxLayout(mainContent);
    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightWidget);
    setCentralWidget(mainContent);

    // Signals / slots
    // Buttons
    connect(addEntryButton, SIGNAL(pressed()), entryView, SLOT(triggerAddEntryMode()));
    connect(delEntryButton, SIGNAL(pressed()), entryView, SLOT(triggerDeleteEntryMode()));
    // Search model
    connect(entryManager, &EntryManager::entryListChanged, searchModel, &SearchModel::updateEntrynames);
    // Entry list model
    connect(entryManager, &EntryManager::entryListChanged, entryListModel, &EntryListModel::updateEntries);
    connect(searchBar, &SearchBar::textCleared, entryListModel, &EntryListModel::clearFilter);
    connect(searchCompleter, qOverload<const QString&>(&QCompleter::activated), entryListModel, &EntryListModel::filter);
    // Entry interaction widget
    connect(entryListView, SIGNAL(entrySelected(Entry)), entryView, SLOT(displayEntry(Entry)));
    connect(entryManager, SIGNAL(entryAdded(Entry)), entryView, SLOT(displayEntry(Entry)));
    connect(entryManager, SIGNAL(entryEdited(Entry)), entryView, SLOT(displayEntry(Entry)));
    connect(entryManager, SIGNAL(entryReset(Entry)), entryView, SLOT(displayEntry(Entry)));
    // Entry manager requests
    connect(entryView, SIGNAL(addEntryConfirmed(Entry)), entryManager, SLOT(addEntry(Entry)));
    connect(entryView, SIGNAL(deleteEntryConfirmed(Entry)), entryManager, SLOT(delEntry(Entry)));
    connect(entryView, SIGNAL(editPasswordConfirmed(Entry)), entryManager, SLOT(resetEntry(Entry)));
    connect(entryView, SIGNAL(editEntrynameConfirmed(Entry,Entry)), entryManager, SLOT(editEntry(Entry,Entry)));
    connect(entryView, SIGNAL(editUsernameConfirmed(Entry,Entry)), entryManager, SLOT(editEntry(Entry,Entry)));
    // Login window
    connect(loginWindow, SIGNAL(rejected()), this, SLOT(close()));
    connect(loginWindow, SIGNAL(authentified(QString,QString)), entryManager, SLOT(init(QString,QString)));

    loginWindow->show();
}

} // namespace pwm
