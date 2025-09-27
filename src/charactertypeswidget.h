// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef CHARACTERTYPESWIDGET_H
#define CHARACTERTYPESWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QButtonGroup>


namespace pwm {

class CharacterTypesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterTypesWidget(QWidget* parent = nullptr);
    /**
     * @brief Return true if no box is checked; false otherwise.
     */
    bool nothingChecked() const;

public slots:
    /**
     * @brief Clear boxes' state to unchecked.
     */
    void clear();

private:
    QHBoxLayout* mainLayout;

    QCheckBox *enableLowCaseBox;
    QCheckBox *enableUpCaseBox;
    QCheckBox *enableNumbersBox;
    QCheckBox *enableSpecialsBox;

    QButtonGroup* checkBoxesGroup;
};

} // namespace pwm

#endif // CHARACTERTYPESWIDGET_H
