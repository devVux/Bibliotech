#include "FormVisitor.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>


void FormVisitor::visit(Film& film) {
	pDialog = new QDialog(pParent);
	pDialog->setWindowTitle("Edit Film");

	QFormLayout* formLayout = new QFormLayout(pDialog);

	QLineEdit* titleEdit = new QLineEdit(film.title());
	QLineEdit* directorEdit = new QLineEdit(film.director());
	QSpinBox* yearEdit = new QSpinBox();
	yearEdit->setValue(film.year());

	formLayout->addRow("Title:", titleEdit);
	formLayout->addRow("Director:", directorEdit);
	formLayout->addRow("Year:", yearEdit);

	QPushButton* saveButton = new QPushButton("Save");
	formLayout->addWidget(saveButton);

    QObject::connect(saveButton, &QPushButton::clicked, saveButton, [this, &film, titleEdit, directorEdit, yearEdit]() {
		film.title(titleEdit->text());
		film.director(directorEdit->text());
		film.year(yearEdit->value());

		film.commitChanges();
		pDialog->accept();
	});

	pDialog->setLayout(formLayout);
}

void FormVisitor::visit(Book& book) {
    pDialog = new QDialog(pParent);
    pDialog->setWindowTitle("Edit Book");

    QFormLayout* formLayout = new QFormLayout(pDialog);

    QLineEdit* titleEdit = new QLineEdit(book.title());
    QLineEdit* publisherEdit = new QLineEdit(book.publisher());
    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setValue(book.year());

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Publisher:", publisherEdit);
    formLayout->addRow("Year:", yearEdit);

    QPushButton* saveButton = new QPushButton("Save");
    formLayout->addWidget(saveButton);

    QObject::connect(saveButton, &QPushButton::clicked, saveButton, [this, &book, titleEdit, publisherEdit, yearEdit]() {
        book.title(titleEdit->text());
        book.publisher(publisherEdit->text());
        book.year(yearEdit->value());

        book.commitChanges();
        pDialog->accept();
    });

    pDialog->setLayout(formLayout);
}

