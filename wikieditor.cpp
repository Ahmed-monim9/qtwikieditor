#include "wikieditor.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>

WikiEditor::WikiEditor(QWidget *parent) : QWidget(parent) {
    editor = new QTextEdit(this);
    saveButton = new QPushButton("حفظ", this);
    loadButton = new QPushButton("فتح", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(editor);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);

    connect(saveButton, &QPushButton::clicked, this, &WikiEditor::saveDocument);
    connect(loadButton, &QPushButton::clicked, this, &WikiEditor::loadDocument);

    setupDatabase();
}

WikiEditor::~WikiEditor() {
    db.close();
}

void WikiEditor::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("wiki.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS documents (id INTEGER PRIMARY KEY, content TEXT)");
}

void WikiEditor::saveDocument() {
    QString content = editor->toPlainText();
    QSqlQuery query;
    query.prepare("INSERT INTO documents (content) VALUES (:content)");
    query.bindValue(":content", content);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to save document");
    } else {
        QMessageBox::information(this, "Success", "Document saved successfully");
    }
}

void WikiEditor::loadDocument() {
    QSqlQuery query;
    query.exec("SELECT content FROM documents ORDER BY id DESC LIMIT 1");

    if (query.next()) {
        QString content = query.value(0).toString();
        editor->setPlainText(content);
    } else {
        QMessageBox::warning(this, "Error", "No documents found");
    }
}
