// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "charactertypeswidget.h"

namespace pwm {

CharacterTypesWidget::CharacterTypesWidget(QWidget *parent)
    : QWidget{parent}
{
    enableLowCaseBox = new QCheckBox(QString("a..z"));
    enableUpCaseBox = new QCheckBox(QString("A..Z"));
    enableNumbersBox = new QCheckBox(QString("0..9"));
    enableSpecialsBox = new QCheckBox(QString("$..!"));

    checkBoxesGroup = new QButtonGroup();
    checkBoxesGroup->setExclusive(false);
    checkBoxesGroup->addButton(enableLowCaseBox, 0);
    checkBoxesGroup->addButton(enableUpCaseBox, 1);
    checkBoxesGroup->addButton(enableNumbersBox, 2);
    checkBoxesGroup->addButton(enableSpecialsBox, 3);

    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(enableLowCaseBox, 1, Qt::AlignHCenter);
    mainLayout->addWidget(enableUpCaseBox, 1, Qt::AlignHCenter);
    mainLayout->addWidget(enableNumbersBox, 1, Qt::AlignHCenter);
    mainLayout->addWidget(enableSpecialsBox, 1, Qt::AlignHCenter);
}

bool CharacterTypesWidget::nothingChecked() const
{
    if (checkBoxesGroup->checkedId() == -1)
        return true;

    return false;
}

void CharacterTypesWidget::clear()
{
    foreach (auto checkBoxes, checkBoxesGroup->buttons())
        checkBoxes->setChecked(false);
}

} // namespace pwm
