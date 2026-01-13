// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "passwordlengthslider.h"

namespace pwm {

PasswordLengthSlider::PasswordLengthSlider(const int pwdMaxLength, QWidget* parent)
    : QWidget(parent)
{
    // Slider
    lengthSlider = new QSlider(Qt::Horizontal);
    lengthSlider->setMinimum(1);
    lengthSlider->setMaximum(pwdMaxLength);
    lengthSlider->setValue(defaultValue);

    // Label
    lengthLabel = new QLabel();
    lengthLabel->setNum(lengthSlider->value());
    lengthLabel->setAlignment(Qt::AlignCenter);
    lengthLabel->setMinimumWidth(lengthLabel->sizeHint().height());

    // Buttons
    increaseLengthButton = new QPushButton("+");
    increaseLengthButton->setFixedWidth(increaseLengthButton->sizeHint().height());
    decreaseLengthButton = new QPushButton("-");
    decreaseLengthButton->setFixedWidth(increaseLengthButton->sizeHint().height());

    // Layout
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(lengthLabel);
    mainLayout->addWidget(decreaseLengthButton);
    mainLayout->addWidget(lengthSlider, 1);
    mainLayout->addWidget(increaseLengthButton);

    // Signals
    connect(lengthSlider, SIGNAL(valueChanged(int)), lengthLabel, SLOT(setNum(int)));
    connect(decreaseLengthButton, SIGNAL(pressed()), this, SLOT(decreaseLength()));
    connect(increaseLengthButton, SIGNAL(pressed()), this, SLOT(increaseLength()));
}

} // namespace pwm
