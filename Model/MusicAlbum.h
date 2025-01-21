#pragma once
#include "Media.h"

class MusicAlbulm : public Media {

private:
    QString mArtist;
    QString mGenre;
    uint32_t mTrackCount;

public:
    MusicAlbulm(const QString& title,
                const QString& publisher,
                uint32_t year,
                const QString& artist,
                const QString& genre,
                uint32_t trackCount)
        : Media(title, publisher, year),
          mArtist(artist),
          mGenre(genre),
          mTrackCount(trackCount)
    { }

    virtual void accept(Visitor* visitor) override;
    virtual bool mathes(const QString& s) const override;

    void artist(const QString& artist) { mArtist = artist; mDirty = true; }
    void genre(const QString& genre)   { mGenre  = genre;  mDirty = true; }
    void trackCount(uint32_t count)    { mTrackCount = count; mDirty = true; }

    const QString& artist() const      { return mArtist; }
    const QString& genre() const       { return mGenre; }
    uint32_t trackCount() const        { return mTrackCount; }
};
