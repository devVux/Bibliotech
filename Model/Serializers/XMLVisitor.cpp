#include "XMLVisitor.h"

void XMLVisitor::visit(Film& film) {
	mElement = mDocument.createElement("Film");
	mElement.setAttribute("title", film.title());
	mElement.setAttribute("publisher", film.publisher());
	mElement.setAttribute("year", film.year());
	mElement.setAttribute("director", film.director());
	mElement.setAttribute("plot", film.plot());
	mElement.setAttribute("duration", film.duration());
}

void XMLVisitor::visit(Book& book) {
	mElement = mDocument.createElement("Book");
	mElement.setAttribute("title", book.title());
	mElement.setAttribute("publisher", book.publisher());
	mElement.setAttribute("year", book.year());
	mElement.setAttribute("author", book.author());
	mElement.setAttribute("plot", book.plot());
}
