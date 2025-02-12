#pragma once

#include <memory>
#include <vector>

#include "Observer.h"
#include "Media.h"

class Biblioteca;
using Model = Biblioteca;
using ModelPtr = std::shared_ptr<Model>;


struct ModelData {
	const std::vector<MediaPtr> medias;
	const QString& query { };
};

class Biblioteca: public Subject<ModelData>, public ObserverNoParameters {

	public:

		void addMedia(const MediaPtr& media);
		void removeMedia(const MediaPtr& media);

        std::vector<MediaPtr> search(const QString& s);
		
		void clear();

        const std::vector<MediaPtr> media() const { return mMedia; }
		void setMedia(const std::vector<MediaPtr>& media) { mMedia = media; notifyAll({ mMedia });  }

		auto begin() { return mMedia.begin(); }
		auto end() { return mMedia.end(); }
		auto begin() const { return mMedia.begin(); }
		auto end() const { return mMedia.end(); }
	

	protected:

        virtual void update() override { notifyAll({ mMedia }); }


	private:

		std::vector<MediaPtr> mMedia;

};
