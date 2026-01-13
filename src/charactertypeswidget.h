// Copyright (C) 2026 Pierre Desbruns
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
     * @brief Return a number btw. 0 and 15 corresponding to checked boxes.
     * @example 0b0000 (0): nothing is checed.
     * @example 0b1000 (8): low case.
     * @example 0b0100 (4): upper case.
     * @example 0b0010 (2): numbers.
     * @example 0b0001 (1): special characters.
     * @example 0b1100 (12): low and upper case.
     */
    int checkedBoxes() const;

public slots:
    /**
     * @brief Clear boxes' state to checked.
     */
    void clear();

private:
    QHBoxLayout* mainLayout;

    QCheckBox* enableLowCaseBox;
    QCheckBox* enableUpCaseBox;
    QCheckBox* enableNumbersBox;
    QCheckBox* enableSpecialsBox;

    QButtonGroup* checkBoxesGroup;
};

} // namespace pwm

#endif // CHARACTERTYPESWIDGET_H
