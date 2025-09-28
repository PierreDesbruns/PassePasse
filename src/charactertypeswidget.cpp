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

    clear();
}

int CharacterTypesWidget::checkedBoxes() const
{
    int checked = 0;

    foreach (auto checkBox, checkBoxesGroup->buttons())
    {
        checked <<= 1;
        if (checkBox->isChecked())
            checked++;
    }

    return checked;
}

void CharacterTypesWidget::clear()
{
    foreach (auto checkBox, checkBoxesGroup->buttons())
        checkBox->setChecked(true);
}

} // namespace pwm
