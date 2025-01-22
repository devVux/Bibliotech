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
// 
void FormVisitor::visit(MusicAlbum& album) {
    pDialog = new QDialog(pParent);
    pDialog->setWindowTitle("Edit Music Album");

    QFormLayout* formLayout = new QFormLayout(pDialog);

    
    QLineEdit* titleEdit = new QLineEdit(album.title());
    QLineEdit* publisherEdit = new QLineEdit(album.publisher());
    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setValue(album.year());

    
    QLineEdit* artistEdit = new QLineEdit(album.artist());
    QLineEdit* genreEdit = new QLineEdit(album.genre());
    QSpinBox* trackCountEdit = new QSpinBox();
    trackCountEdit->setValue(album.trackCount());

    
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Publisher:", publisherEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Artist:", artistEdit);
    formLayout->addRow("Genre:", genreEdit);
    formLayout->addRow("Tracks:", trackCountEdit);

    QPushButton* saveButton = new QPushButton("Save");
    formLayout->addWidget(saveButton);

    QObject::connect(saveButton, &QPushButton::clicked,
                     saveButton, 
                     [this, &album,
                      titleEdit, publisherEdit, yearEdit,
                      artistEdit, genreEdit, trackCountEdit]()
    {
        album.title(titleEdit->text());
        album.publisher(publisherEdit->text());
        album.year(yearEdit->value());
        album.artist(artistEdit->text());
        album.genre(genreEdit->text());
        album.trackCount(trackCountEdit->value());

        
        album.commitChanges();
        pDialog->accept();
    });

    pDialog->setLayout(formLayout);
}

