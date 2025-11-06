// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>


namespace pwm {

class SearchBar : public QLineEdit
{
    Q_OBJECT

public:
    SearchBar(QWidget* parent = nullptr);

signals:
    /**
     * @brief Emitted when search bar has been cleared.
     */
    void textCleared();
};

} // namespace pwm

#endif // SEARCHBAR_H
