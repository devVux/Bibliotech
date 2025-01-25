#include "MusicAlbum.h"
#include "Visitor.h"

void MusicAlbum::accept(Visitor* visitor) {
    visitor->visit(*this);
}

bool MusicAlbum::mathes(const QString& s) const {
    return mTitle.contains(s, Qt::CaseInsensitive) ||
           mArtist.contains(s, Qt::CaseInsensitive) ||
           mGenre.contains(s, Qt::CaseInsensitive);
}
