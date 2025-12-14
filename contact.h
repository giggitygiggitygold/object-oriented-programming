#pragma once
#include <QString>
#include <QDate>

class Contact {
public:
    QString firstName;
    QString lastName;
    QString middleName;
    QString address;
    QDate birthDate;
    QString email;
    QString phoneWork;
    QString phoneHome;
    QString phoneMobile;

    Contact() = default;

    // Конструктор для создания контакта
    Contact(const QString &fn, const QString &ln, const QString &mn,
            const QString &addr, const QDate &bd, const QString &em,
            const QString &pw, const QString &ph, const QString &pm)
        : firstName(fn), lastName(ln), middleName(mn),
        address(addr), birthDate(bd), email(em),
        phoneWork(pw), phoneHome(ph), phoneMobile(pm) {}

    // Метод для получения строки для записи в файл
    QString toFileString() const;

    // Метод для восстановления контакта из строки файла
    static Contact fromFileString(const QString &line);
};
