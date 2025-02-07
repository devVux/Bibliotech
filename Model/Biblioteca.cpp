#include "Biblioteca.h"

void Biblioteca::addMedia(const MediaPtr& media) {
    media->registerObserver(this);
	mMedia.push_back(media);
	notifyAll({ mMedia });
}

void Biblioteca::removeMedia(const MediaPtr& media) {
	auto it = std::find(mMedia.begin(), mMedia.end(), media);
	if (it != mMedia.end()) {
		mMedia.erase(it);
		notifyAll({ mMedia });
	}
}

std::vector<MediaPtr> Biblioteca::search(const QString& s) {
	std::vector<MediaPtr> result;
    for (MediaPtr media : mMedia)
		if (media->mathes(s))
            result.push_back(media);

    notifyAll({ result });

	return result;
}

void Biblioteca::clear() {
	mMedia.clear();
	notifyAll({ mMedia });
}

