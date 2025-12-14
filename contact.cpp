#include "contact.h"
#include <QStringList>

QString Contact::toFileString() const {
    return QString("%1;%2;%3;%4;%5;%6;%7;%8;%9")
    .arg(firstName)
        .arg(lastName)
        .arg(middleName)
        .arg(address)
        .arg(birthDate.toString("yyyy-MM-dd"))
        .arg(email)
        .arg(phoneWork)
        .arg(phoneHome)
        .arg(phoneMobile);
}

Contact Contact::fromFileString(const QString &line) {
    QStringList parts = line.split(';', Qt::SkipEmptyParts);
    if (parts.size() != 9) {
        return Contact(); // Возвращаем пустой контакт при ошибке
    }

    Contact c;
    c.firstName = parts[0];
    c.lastName = parts[1];
    c.middleName = parts[2];
    c.address = parts[3];
    c.birthDate = QDate::fromString(parts[4], "yyyy-MM-dd");
    c.email = parts[5];
    c.phoneWork = parts[6];
    c.phoneHome = parts[7];
    c.phoneMobile = parts[8];

    return c;
}
