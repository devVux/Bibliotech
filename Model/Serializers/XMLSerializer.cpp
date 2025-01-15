#include "XMLSerializer.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

bool XMLSerializer::save(const QString& filename, const Biblioteca& biblioteca) {
	QDomDocument document;

	QDomElement root = document.createElement("Biblioteca");
	document.appendChild(root);

    for (const MediaPtr& media : biblioteca) {
		media->accept(&mVisitor);
        root.appendChild(mVisitor.element());
	}

	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream stream(&file);
	stream << document.toString();
	file.close();

    return true;
}

bool XMLSerializer::load(const QString& filename, Biblioteca& biblioteca) const {
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "Failed to open file" << filename;
		return false;
	}

	QDomDocument document;
	if (!document.setContent(&file)) {
		qWarning() << "Failed to parse XML content";
		return false;
	}

	QDomElement root = document.documentElement();
	if (root.tagName() != "Biblioteca") {
		qWarning() << "Invalid root element in XML file";
		return false;
	}

    biblioteca.clear();

	QDomNode node = root.firstChild();
	while (!node.isNull()) {
		if (node.isElement()) {
			QDomElement element = node.toElement();
			if (element.tagName() == "Film") {
				QString title = element.attribute("title");
				QString publisher = element.attribute("publisher");
				uint32_t year = element.attribute("year").toUInt();
				QString director = element.attribute("director");
				QString plot = element.attribute("plot");
				uint32_t duration = element.attribute("duration").toUInt();

				MediaPtr film = std::make_shared<Film>(title, publisher, year, director, plot, duration);
				biblioteca.addMedia(film);

			} else if (element.tagName() == "Book") {
				QString title = element.attribute("title");
				QString publisher = element.attribute("publisher");
				uint32_t year = element.attribute("year").toUInt();
				QString author = element.attribute("author");
				QString plot = element.attribute("plot");

				MediaPtr book = std::make_shared<Book>(title, publisher, year, author, plot);
				biblioteca.addMedia(book);

			}
		}
		node = node.nextSibling();
	}

	return true;
}
