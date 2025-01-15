#include "Film.h"

#include "Visitor.h"

void Film::accept(Visitor* visitor) {
	visitor->visit(*this);
}

bool Film::mathes(const QString& s) const {
    return	
		mTitle.contains(s, Qt::CaseInsensitive) ||
        mDirector.contains(s, Qt::CaseInsensitive) ||
        mPublisher.contains(s, Qt::CaseInsensitive);
}
