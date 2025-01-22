#include "View.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>

#include <QtVisitor.h>
#include <FormVisitor.h>


void View::init() {

	auto toolbar = new QToolBar(this);
	addToolBar(toolbar);

	auto loadAction = toolbar->addAction("Load");
	auto saveAction = toolbar->addAction("Save");

	auto addBookAction = toolbar->addAction("Add Book");
	auto addFilmAction = toolbar->addAction("Add Film");

	auto searchAction = toolbar->addAction("Search");
	auto resetAction = toolbar->addAction("Reset");

	connect(addBookAction, &QAction::triggered, this, &View::addBookButtonClicked);
	connect(addFilmAction, &QAction::triggered, this, &View::addFilmButtonClicked);
	
	connect(loadAction, &QAction::triggered, this, [this]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Load File", "dump.xml", "XML Files (*.xml);;All Files (*)");
		if (!filePath.isEmpty())
			emit loadButtonClicked(filePath);
	});
	connect(saveAction, &QAction::triggered, this, [this]() {
		QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "XML Files (*.xml);;All Files (*)");
		if (!filePath.isEmpty())
			emit saveButtonClicked(filePath);
	});

    connect(searchAction, &QAction::triggered, this, [this]() {
		bool ok;
		QString query = QInputDialog::getText(this, "Search", "Enter search query:", QLineEdit::Normal, "", &ok);
		if (ok && !query.isEmpty())
			emit searchButtonClicked(query);
	});
	connect(resetAction, &QAction::triggered, this, &View::resetButtonClicked);


    setCentralWidget(pContent);

}

void View::update(void* data) {
    const QString& filter = *static_cast<QString*>(data);
	display(pModel->search(filter));
}

void View::display(const std::vector<MediaPtr>& medias) {
	auto layout = pContent->layout();
	if (!layout)
		layout = new QVBoxLayout(pContent);

	clearLayout(layout);


	QtVisitor visitor(pContent);
    for (const MediaPtr& media : medias) {
		media->accept(&visitor);

		auto w = visitor.widget();
		connect(w, &MediaWidget::deleteButtonClicked, this, [this, media]() {
			emit removeMedia(media);
		});
		connect(w, &MediaWidget::editButtonClicked, this, [this, media]() {
			FormVisitor formVisitor(pContent);
			media->accept(&formVisitor);
            formVisitor.dialog()->exec();
		});

		layout->addWidget(w);
	}

}

void View::clearLayout(QLayout* layout) {
	if (!layout) return;

	while (QLayoutItem* item = layout->takeAt(0)) {
		delete item->widget();
		delete item;
	}
}

