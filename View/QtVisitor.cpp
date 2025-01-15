#include "QtVisitor.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

void QtVisitor::visit(Film& film) {

	pWidget = new MediaWidget(pParent);
    QVBoxLayout* layout = new QVBoxLayout(pWidget);

	QLabel* titleLabel = new QLabel("Title: " + film.title(), pWidget);
	QLabel* directorLabel = new QLabel("Director: " + film.director(), pWidget);
	QLabel* publisherLabel = new QLabel("Publisher: " + film.publisher(), pWidget);
	QLabel* yearLabel = new QLabel("Year: " + QString::number(film.year()), pWidget);
	QLabel* durationLabel = new QLabel("Duration: " + QString::number(film.duration()) + " minutes", pWidget);
	QLabel* plotLabel = new QLabel("Plot: " + film.plot(), pWidget);

	QPushButton* deleteButton = new QPushButton("Delete", pWidget);
    QObject::connect(deleteButton, &QPushButton::clicked, pWidget, &MediaWidget::deleteButtonClicked);
	
	QPushButton* editButton = new QPushButton("Edit", pWidget);
    QObject::connect(editButton, &QPushButton::clicked, pWidget, &MediaWidget::editButtonClicked);

	layout->addWidget(titleLabel);
	layout->addWidget(directorLabel);
	layout->addWidget(publisherLabel);
	layout->addWidget(yearLabel);
	layout->addWidget(durationLabel);
	layout->addWidget(plotLabel);
	layout->addWidget(editButton);
	layout->addWidget(deleteButton);

}

void QtVisitor::visit(Book& book) {

    pWidget = new MediaWidget(pParent);
    QVBoxLayout* layout = new QVBoxLayout(pWidget);

	QLabel* titleLabel = new QLabel("Title: " + book.title(), pWidget);
	QLabel* authorLabel = new QLabel("Author: " + book.author(), pWidget);
	QLabel* publisherLabel = new QLabel("Publisher: " + book.publisher(), pWidget);
	QLabel* yearLabel = new QLabel("Year: " + QString::number(book.year()), pWidget);
	QLabel* plotLabel = new QLabel("Plot: " + book.plot(), pWidget);

	QPushButton* deleteButton = new QPushButton("Delete");
	QObject::connect(deleteButton, &QPushButton::clicked, pWidget, &MediaWidget::deleteButtonClicked);

	QPushButton* editButton = new QPushButton("Edit", pWidget);
	QObject::connect(editButton, &QPushButton::clicked, pWidget, &MediaWidget::editButtonClicked);

	layout->addWidget(titleLabel);
	layout->addWidget(authorLabel);
	layout->addWidget(publisherLabel);
	layout->addWidget(yearLabel);
	layout->addWidget(plotLabel);
	layout->addWidget(editButton);
	layout->addWidget(deleteButton);

}
