#include "Book.h"

#include "Visitor.h"

void Book::accept(Visitor* visitor) {
    visitor->visit(*this);
}

bool Book::mathes(const QString& s) const {
	return	
		mTitle.contains(s, Qt::CaseInsensitive) ||
		mAuthor.contains(s, Qt::CaseInsensitive) ||
		mPlot.contains(s, Qt::CaseInsensitive);
}
