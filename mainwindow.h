#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include "contact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddContact();
    void onEditContact();
    void onDeleteContact();
    void onSearch();
    void onSortByFirstName();
    void onSortByLastName();
    void onSortByEmail();
    void onSortByPhone();
    void onLoadFromFile();
    void onSaveToFile();

    void onTableClicked(int row, int column);

private:
    void loadContacts();
    void saveContacts();
    void updateTable();
    bool validateInput();
    void clearInputFields();
    void populateInputFields(int row);

    Ui::MainWindow *ui;
    QVector<Contact> contacts;
    QSortFilterProxyModel *proxyModel;
    int currentEditRow = -1;

    // Поля ввода
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *middleNameEdit;
    QLineEdit *addressEdit;
    QLineEdit *birthDateEdit;
    QLineEdit *emailEdit;
    QLineEdit *phoneWorkEdit;
    QLineEdit *phoneHomeEdit;
    QLineEdit *phoneMobileEdit;

    // Кнопки
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *searchButton;
    QPushButton *sortByFirstNameBtn;
    QPushButton *sortByLastNameBtn;
    QPushButton *sortByEmailBtn;
    QPushButton *sortByPhoneBtn;
    QPushButton *loadButton;
    QPushButton *saveButton;

    // Таблица
    QTableWidget *tableWidget;

    // Поиск
    QLineEdit *searchEdit;
};
#endif // MAINWINDOW_H
