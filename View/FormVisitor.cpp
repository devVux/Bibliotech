#include "FormVisitor.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>


void FormVisitor::visit(Film& film) {
    pFormWidget = new QWidget(pParent);
    pFormWidget->setWindowTitle("Edit Film");
    QFormLayout* formLayout = new QFormLayout(pFormWidget);

    QLineEdit* titleEdit = new QLineEdit(film.title());
    QLineEdit* publisherEdit = new QLineEdit(film.publisher());
    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1800, 2100);
    yearEdit->setValue(film.year());
    QLineEdit* directorEdit = new QLineEdit(film.director());
    QLineEdit* plotEdit = new QLineEdit(film.plot());
    QSpinBox* durationEdit = new QSpinBox();
    durationEdit->setRange(1, 500);
    durationEdit->setValue(film.duration());

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Publisher:", publisherEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Director:", directorEdit);
    formLayout->addRow("Plot:", plotEdit);
    formLayout->addRow("Duration:", durationEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    QWidget* form = pFormWidget; // VAR LOC per lambda

    QObject::connect(saveButton, &QPushButton::clicked, form, [=, &film]() {
        this->saved = true; // utente ha premuto save
        film.title(titleEdit->text());
        film.publisher(publisherEdit->text());
        film.year(static_cast<uint32_t>(yearEdit->value()));
        film.director(directorEdit->text());
        film.plot(plotEdit->text());
        film.duration(static_cast<uint32_t>(durationEdit->value()));
        film.commitChanges();
        if(onFinish)
            onFinish(form);
    });
    QObject::connect(cancelButton, &QPushButton::clicked, form, [&]() {
        if(onFinish)
            onFinish(form);
    });
}


void FormVisitor::visit(Book& book) {
    pFormWidget = new QWidget(pParent);
    pFormWidget->setWindowTitle("Edit Book");
    QFormLayout* formLayout = new QFormLayout(pFormWidget);

    QLineEdit* titleEdit = new QLineEdit(book.title());
    QLineEdit* publisherEdit = new QLineEdit(book.publisher());
    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1800, 2100);
    yearEdit->setValue(book.year());
    QLineEdit* authorEdit = new QLineEdit(book.author());
    QLineEdit* plotEdit = new QLineEdit(book.plot());

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Publisher:", publisherEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Author:", authorEdit);
    formLayout->addRow("Plot:", plotEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    QWidget* form = pFormWidget;
    QObject::connect(saveButton, &QPushButton::clicked, form, [=, &book]() {
        this->saved = true;
        book.title(titleEdit->text());
        book.publisher(publisherEdit->text());
        book.year(static_cast<uint32_t>(yearEdit->value()));
        book.author(authorEdit->text());
        book.plot(plotEdit->text());
        book.commitChanges();
        if(onFinish)
            onFinish(form);
    });
    QObject::connect(cancelButton, &QPushButton::clicked, form, [&]() {
        if(onFinish)
            onFinish(form);
    });
}


void FormVisitor::visit(MusicAlbum& album) {
    pFormWidget = new QWidget(pParent);
    pFormWidget->setWindowTitle("Edit Music Album");
    QFormLayout* formLayout = new QFormLayout(pFormWidget);

    QLineEdit* titleEdit = new QLineEdit(album.title());
    QLineEdit* publisherEdit = new QLineEdit(album.publisher());
    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1800, 2100);
    yearEdit->setValue(album.year());
    QLineEdit* artistEdit = new QLineEdit(album.artist());
    QLineEdit* genreEdit = new QLineEdit(album.genre());
    QSpinBox* trackCountEdit = new QSpinBox();
    trackCountEdit->setRange(1, 100);
    trackCountEdit->setValue(album.trackCount());

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Publisher:", publisherEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Artist:", artistEdit);
    formLayout->addRow("Genre:", genreEdit);
    formLayout->addRow("Tracks:", trackCountEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    formLayout->addRow(buttonLayout);

    QWidget* form = pFormWidget;
    QObject::connect(saveButton, &QPushButton::clicked, form, [=, &album]() {
        this->saved = true;
        album.title(titleEdit->text());
        album.publisher(publisherEdit->text());
        album.year(static_cast<uint32_t>(yearEdit->value()));
        album.artist(artistEdit->text());
        album.genre(genreEdit->text());
        album.trackCount(static_cast<uint32_t>(trackCountEdit->value()));
        album.commitChanges();
        if(onFinish)
            onFinish(form);
    });
    QObject::connect(cancelButton, &QPushButton::clicked, form, [&]() {
        if(onFinish)
            onFinish(form);
    });
}
