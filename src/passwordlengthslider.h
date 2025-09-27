// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef PASSWORDLENGTHSLIDER_H
#define PASSWORDLENGTHSLIDER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

namespace pwm {

class PasswordLengthSlider : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordLengthSlider(const int pwdMaxLength, QWidget* parent = nullptr);

    int value() const { return lengthSlider->value(); }
    void setValue(const int value) { lengthSlider->setValue(value); }

public slots:
    /**
     * @brief Inrease value of 1.
     */
    void increaseLength() { lengthSlider->setValue(lengthSlider->value()+1); }
    /**
     * @brief Decrease value of 1.
     */
    void decreaseLength() { lengthSlider->setValue(lengthSlider->value()-1); }
    /**
     * @brief Clear slider's value to default.
     */
    void clear() { setValue(12); }

private:
    // Widgets
    QHBoxLayout* mainLayout;
    QSlider* lengthSlider;
    QLabel* lengthLabel;
    QPushButton* increaseLengthButton;
    QPushButton* decreaseLengthButton;
};

} // namespace pwm

#endif // PASSWORDLENGTHSLIDER_H
