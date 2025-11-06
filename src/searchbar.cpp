#include "searchbar.h"

namespace pwm {

SearchBar::SearchBar(QWidget *parent)
    : QLineEdit(parent)
{
    connect(
        this, &QLineEdit::textChanged,
        this, [this](const QString& text) { if (text.isEmpty()) emit textCleared(); }
    );
}

} // namespace pwm
