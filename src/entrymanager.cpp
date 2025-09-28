#include "entrymanager.h"

namespace pwm {

EntryManager::EntryManager(QObject* parent)
    : QObject{parent}
{

}

void EntryManager::addEntry(const QString &entryname, const QString &username, const int passwordLength, const int characterTypes)
{
    Entry testEntry(entryname, username);

    // Verifications
    if (m_entryList.contains(testEntry))
    {
        qWarning() << "Entry Manager: Did not add entry because entry already exists.";
        return;
    }
    if (passwordLength < 1)
    {
        qWarning() << "Entry Manager: Did not add entry because password is too short.";
        return;
    }
    if ((characterTypes < 0) || (characterTypes > 15))
    {
        qWarning() << "Entry Manager: Did not add entry because character types are wrong.";
        return;
    }

    bool hasLowCase = ((characterTypes & 0b1000) != 0);
    bool hasUpCase = ((characterTypes & 0b0100) != 0);
    bool hasNumbers = ((characterTypes & 0b0010) != 0);
    bool hasSpecials = ((characterTypes & 0b0001) != 0);

    QString password = generatePassword(passwordLength, hasLowCase, hasUpCase, hasNumbers, hasSpecials);
    if (password.isEmpty())
    {
        qWarning() << "Entry Manager: An error occured during password generation. No password has been generated.";
        return;
    }

    QString date = QDate::currentDate().toString("yyyy.MM.dd");

    m_entryList << Entry(entryname, username, password, date);

    emit entryAdded();
}

} // namespace pwm
