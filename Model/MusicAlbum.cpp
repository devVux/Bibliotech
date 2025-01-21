#include "MusicAlbulm.h"
#include "Visitor.h"

void MusicAlbulm::accept(Visitor* visitor) {
    visitor->visit(*this);
}

bool MusicAlbulm::mathes(const QString& s) const {
    return mTitle.contains(s, Qt::CaseInsensitive) ||
           mArtist.contains(s, Qt::CaseInsensitive) ||
           mGenre.contains(s, Qt::CaseInsensitive);
}
