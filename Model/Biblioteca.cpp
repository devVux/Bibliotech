#include "Biblioteca.h"

void Biblioteca::addMedia(const MediaPtr& media) {
	media->registerObserver(this);
	mMedia.push_back(media);
	notifyAll();
}

void Biblioteca::removeMedia(const MediaPtr& media) {
	const auto& it = std::find(mMedia.begin(), mMedia.end(), media);
	if (it != mMedia.end()) {
		mMedia.erase(it);
		notifyAll();
	}
}

std::vector<MediaPtr> Biblioteca::search(const QString& s) const {
	std::vector<MediaPtr> v;
    for (MediaPtr media : mMedia)
		if (media->mathes(s))
			v.push_back(media);

	return v;
}

void Biblioteca::clear() {
	mMedia.erase(mMedia.begin(), mMedia.end());
	notifyAll();
}

