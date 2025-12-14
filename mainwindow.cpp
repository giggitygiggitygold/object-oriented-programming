#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDate>
#include <QMessageBox>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Телефонный справочник");

    // Создаем виджеты
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    middleNameEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    birthDateEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    phoneWorkEdit = new QLineEdit(this);
    phoneHomeEdit = new QLineEdit(this);
    phoneMobileEdit = new QLineEdit(this);

    addButton = new QPushButton("Добавить", this);
    editButton = new QPushButton("Редактировать", this);
    deleteButton = new QPushButton("Удалить", this);
    searchButton = new QPushButton("Поиск", this);
    sortByFirstNameBtn = new QPushButton("Сортировать по Имени", this);
    sortByLastNameBtn = new QPushButton("Сортировать по Фамилии", this);
    sortByEmailBtn = new QPushButton("Сортировать по Email", this);
    sortByPhoneBtn = new QPushButton("Сортировать по Телефону", this);
    loadButton = new QPushButton("Загрузить из файла", this);
    saveButton = new QPushButton("Сохранить в файл", this);

    searchEdit = new QLineEdit(this);
    tableWidget = new QTableWidget(this);

    // Устанавливаем заголовки таблицы
    tableWidget->setColumnCount(9);
    tableWidget->setHorizontalHeaderLabels({
        "Имя", "Фамилия", "Отчество", "Адрес", "Дата рождения",
        "Email", "Рабочий телефон", "Домашний телефон", "Мобильный телефон"
    });

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Лейауты
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QHBoxLayout *sortLayout = new QHBoxLayout();

    // Добавляем поля ввода
    inputLayout->addWidget(new QLabel("Имя:"));
    inputLayout->addWidget(firstNameEdit);
    inputLayout->addWidget(new QLabel("Фамилия:"));
    inputLayout->addWidget(lastNameEdit);
    inputLayout->addWidget(new QLabel("Отчество:"));
    inputLayout->addWidget(middleNameEdit);
    inputLayout->addWidget(new QLabel("Адрес:"));
    inputLayout->addWidget(addressEdit);
    inputLayout->addWidget(new QLabel("Дата рождения (гггг-мм-дд):"));
    inputLayout->addWidget(birthDateEdit);
    inputLayout->addWidget(new QLabel("Email:"));
    inputLayout->addWidget(emailEdit);
    inputLayout->addWidget(new QLabel("Рабочий тел.:"));
    inputLayout->addWidget(phoneWorkEdit);
    inputLayout->addWidget(new QLabel("Домашний тел.:"));
    inputLayout->addWidget(phoneHomeEdit);
    inputLayout->addWidget(new QLabel("Мобильный тел.:"));
    inputLayout->addWidget(phoneMobileEdit);

    // Кнопки управления
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);

    // Поиск
    searchLayout->addWidget(new QLabel("Поиск:"));
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    // Сортировка
    sortLayout->addWidget(sortByFirstNameBtn);
    sortLayout->addWidget(sortByLastNameBtn);
    sortLayout->addWidget(sortByEmailBtn);
    sortLayout->addWidget(sortByPhoneBtn);

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(sortLayout);
    mainLayout->addWidget(tableWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Подключаем сигналы
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteContact);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(sortByFirstNameBtn, &QPushButton::clicked, this, &MainWindow::onSortByFirstName);
    connect(sortByLastNameBtn, &QPushButton::clicked, this, &MainWindow::onSortByLastName);
    connect(sortByEmailBtn, &QPushButton::clicked, this, &MainWindow::onSortByEmail);
    connect(sortByPhoneBtn, &QPushButton::clicked, this, &MainWindow::onSortByPhone);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveToFile);
    connect(tableWidget, &QTableWidget::cellClicked, this, [this](int row, int column){
        onTableClicked(row, column);
    });

    // Загружаем данные при старте
    loadContacts();
    updateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddContact() {
    if (!validateInput()) {
        QMessageBox::warning(this, "Ошибка", "Проверьте корректность введенных данных.");
        return;
    }

    Contact c(
        firstNameEdit->text().trimmed(),
        lastNameEdit->text().trimmed(),
        middleNameEdit->text().trimmed(),
        addressEdit->text().trimmed(),
        QDate::fromString(birthDateEdit->text().trimmed(), "yyyy-MM-dd"),
        emailEdit->text().trimmed(),
        phoneWorkEdit->text().trimmed(),
        phoneHomeEdit->text().trimmed(),
        phoneMobileEdit->text().trimmed()
        );

    contacts.append(c);
    updateTable();
    clearInputFields();
    currentEditRow = -1;
    QMessageBox::information(this, "Успех", "Контакт добавлен.");
}

void MainWindow::onEditContact() {
    if (currentEditRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для редактирования.");
        return;
    }

    if (!validateInput()) {
        QMessageBox::warning(this, "Ошибка", "Проверьте корректность введенных данных.");
        return;
    }

    Contact &c = contacts[currentEditRow];
    c.firstName = firstNameEdit->text().trimmed();
    c.lastName = lastNameEdit->text().trimmed();
    c.middleName = middleNameEdit->text().trimmed();
    c.address = addressEdit->text().trimmed();
    c.birthDate = QDate::fromString(birthDateEdit->text().trimmed(), "yyyy-MM-dd");
    c.email = emailEdit->text().trimmed();
    c.phoneWork = phoneWorkEdit->text().trimmed();
    c.phoneHome = phoneHomeEdit->text().trimmed();
    c.phoneMobile = phoneMobileEdit->text().trimmed();

    updateTable();
    clearInputFields();
    currentEditRow = -1;
    QMessageBox::information(this, "Успех", "Контакт обновлен.");
}

void MainWindow::onDeleteContact() {
    if (currentEditRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для удаления.");
        return;
    }

    contacts.removeAt(currentEditRow);
    updateTable();
    clearInputFields();
    currentEditRow = -1;
    QMessageBox::information(this, "Успех", "Контакт удален.");
}

void MainWindow::onSearch() {
    QString searchText = searchEdit->text().trimmed();
    if (searchText.isEmpty()) {
        updateTable();
        return;
    }

    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    for (int i = 0; i < contacts.size(); ++i) {
        const Contact &c = contacts[i];
        if (c.firstName.contains(searchText, Qt::CaseInsensitive) ||
            c.lastName.contains(searchText, Qt::CaseInsensitive) ||
            c.email.contains(searchText, Qt::CaseInsensitive) ||
            c.phoneWork.contains(searchText, Qt::CaseInsensitive) ||
            c.phoneHome.contains(searchText, Qt::CaseInsensitive) ||
            c.phoneMobile.contains(searchText, Qt::CaseInsensitive)) {

            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);

            tableWidget->setItem(row, 0, new QTableWidgetItem(c.firstName));
            tableWidget->setItem(row, 1, new QTableWidgetItem(c.lastName));
            tableWidget->setItem(row, 2, new QTableWidgetItem(c.middleName));
            tableWidget->setItem(row, 3, new QTableWidgetItem(c.address));
            tableWidget->setItem(row, 4, new QTableWidgetItem(c.birthDate.toString("dd.MM.yyyy")));
            tableWidget->setItem(row, 5, new QTableWidgetItem(c.email));
            tableWidget->setItem(row, 6, new QTableWidgetItem(c.phoneWork));
            tableWidget->setItem(row, 7, new QTableWidgetItem(c.phoneHome));
            tableWidget->setItem(row, 8, new QTableWidgetItem(c.phoneMobile));
        }
    }
}

void MainWindow::onSortByFirstName() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b) {
        return a.firstName < b.firstName;
    });
    updateTable();
}

void MainWindow::onSortByLastName() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b) {
        return a.lastName < b.lastName;
    });
    updateTable();
}

void MainWindow::onSortByEmail() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b) {
        return a.email < b.email;
    });
    updateTable();
}

void MainWindow::onSortByPhone() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b) {
        return a.phoneMobile < b.phoneMobile;
    });
    updateTable();
}

void MainWindow::onLoadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    contacts.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.trimmed().isEmpty()) {
            Contact c = Contact::fromFileString(line);
            if (c.firstName.isEmpty() && c.lastName.isEmpty()) continue; // Пропускаем некорректные
            contacts.append(c);
        }
    }
    file.close();
    updateTable();
    QMessageBox::information(this, "Успех", "Данные загружены.");
}

void MainWindow::onSaveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "contacts.txt", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить файл.");
        return;
    }

    QTextStream out(&file);
    for (const Contact &c : contacts) {
        out << c.toFileString() << "\n";
    }
    file.close();
    QMessageBox::information(this, "Успех", "Данные сохранены.");
}

void MainWindow::onTableClicked(int row, int column) {
    (void)column;
    currentEditRow = row;
    populateInputFields(row);
}

void MainWindow::updateTable() {
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    for (int i = 0; i < contacts.size(); ++i) {
        const Contact &c = contacts[i];
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(c.firstName));
        tableWidget->setItem(row, 1, new QTableWidgetItem(c.lastName));
        tableWidget->setItem(row, 2, new QTableWidgetItem(c.middleName));
        tableWidget->setItem(row, 3, new QTableWidgetItem(c.address));
        tableWidget->setItem(row, 4, new QTableWidgetItem(c.birthDate.toString("dd.MM.yyyy")));
        tableWidget->setItem(row, 5, new QTableWidgetItem(c.email));
        tableWidget->setItem(row, 6, new QTableWidgetItem(c.phoneWork));
        tableWidget->setItem(row, 7, new QTableWidgetItem(c.phoneHome));
        tableWidget->setItem(row, 8, new QTableWidgetItem(c.phoneMobile));
    }
}

bool MainWindow::validateInput() {
    // Имя, Фамилия, Отчество — только буквы и цифры, начинаются с буквы, без пробелов в начале/конце
    QRegularExpression nameRegex("^[A-Za-zА-Яа-яЁё0-9][A-Za-zА-Яа-яЁё0-9\\s]*$");
    QString fn = firstNameEdit->text().trimmed();
    QString ln = lastNameEdit->text().trimmed();
    QString mn = middleNameEdit->text().trimmed();

    if (fn.isEmpty() || !nameRegex.match(fn).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Имя должно содержать только буквы и цифры, начинаться с буквы.");
        return false;
    }
    if (ln.isEmpty() || !nameRegex.match(ln).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Фамилия должна содержать только буквы и цифры, начинаться с буквы.");
        return false;
    }
    if (mn.isEmpty() || !nameRegex.match(mn).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Отчество должно содержать только буквы и цифры, начинаться с буквы.");
        return false;
    }

    // Дата рождения
    QDate bd = QDate::fromString(birthDateEdit->text().trimmed(), "yyyy-MM-dd");
    if (!bd.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат даты (гггг-мм-дд).");
        return false;
    }
    if (bd > QDate::currentDate()) {
        QMessageBox::warning(this, "Ошибка", "Дата рождения не может быть в будущем.");
        return false;
    }

    // Email
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QString em = emailEdit->text().trimmed();
    if (em.isEmpty() || !emailRegex.match(em).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат email.");
        return false;
    }

    // Телефоны — проверяем форматы из задания
    QRegularExpression phoneRegex("^\\+?\\d{1,3}?[-. ]?\\(?\\d{1,4}\\)?[-. ]?\\d{1,4}[-. ]?\\d{1,4}[-. ]?\\d{1,9}$");
    QString pw = phoneWorkEdit->text().trimmed();
    QString ph = phoneHomeEdit->text().trimmed();
    QString pm = phoneMobileEdit->text().trimmed();

    if (pw.isEmpty() && ph.isEmpty() && pm.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите хотя бы один телефон.");
        return false;
    }

    if (!pw.isEmpty() && !phoneRegex.match(pw).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат рабочего телефона.");
        return false;
    }
    if (!ph.isEmpty() && !phoneRegex.match(ph).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат домашнего телефона.");
        return false;
    }
    if (!pm.isEmpty() && !phoneRegex.match(pm).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат мобильного телефона.");
        return false;
    }

    return true;
}

void MainWindow::clearInputFields() {
    firstNameEdit->clear();
    lastNameEdit->clear();
    middleNameEdit->clear();
    addressEdit->clear();
    birthDateEdit->clear();
    emailEdit->clear();
    phoneWorkEdit->clear();
    phoneHomeEdit->clear();
    phoneMobileEdit->clear();
    currentEditRow = -1;
}

void MainWindow::populateInputFields(int row) {
    if (row < 0 || row >= contacts.size()) return;

    const Contact &c = contacts[row];
    firstNameEdit->setText(c.firstName);
    lastNameEdit->setText(c.lastName);
    middleNameEdit->setText(c.middleName);
    addressEdit->setText(c.address);
    birthDateEdit->setText(c.birthDate.toString("yyyy-MM-dd"));
    emailEdit->setText(c.email);
    phoneWorkEdit->setText(c.phoneWork);
    phoneHomeEdit->setText(c.phoneHome);
    phoneMobileEdit->setText(c.phoneMobile);
}

void MainWindow::loadContacts() {
    QFile file("contacts.txt");
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (!line.trimmed().isEmpty()) {
                    Contact c = Contact::fromFileString(line);
                    if (c.firstName.isEmpty() && c.lastName.isEmpty()) continue;
                    contacts.append(c);
                }
            }
            file.close();
        }
    }
}

void MainWindow::saveContacts() {
    QFile file("contacts.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Contact &c : contacts) {
            out << c.toFileString() << "\n";
        }
        file.close();
    }
}
