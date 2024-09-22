#ifndef WIKIEDITOR_H
#define WIKIEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>

class WikiEditor : public QWidget {
    Q_OBJECT

public:
    WikiEditor(QWidget *parent = nullptr);
    ~WikiEditor();

private slots:
    void saveDocument();
    void loadDocument();

private:
    QTextEdit *editor;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QSqlDatabase db;

    void setupDatabase();
};

#endif // WIKIEDITOR_H
