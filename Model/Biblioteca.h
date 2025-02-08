#pragma once

#include <memory>
#include <vector>

#include "Observer.h"
#include "Media.h"

using MediaPtr = std::shared_ptr<Media>;

class Biblioteca;
using Model = Biblioteca;
using ModelPtr = std::shared_ptr<Model>;

class Biblioteca: public Subject, public Observer {

	public:

		void addMedia(const MediaPtr& media);
		void removeMedia(const MediaPtr& media);

		std::vector<MediaPtr> search(const QString& s) const;
		
		void clear();

        const std::vector<MediaPtr> media() const { return mMedia; }
		void setMedia(const std::vector<MediaPtr>& media) { mMedia = media; notifyAll();  }

		auto begin() { return mMedia.begin(); }
		auto end() { return mMedia.end(); }
		auto begin() const { return mMedia.begin(); }
		auto end() const { return mMedia.end(); }
	

	protected:

		virtual void notifyAll() override {
			for (Observer* observer : mObservers)
				observer->update(nullptr);
		}

        virtual void update(void*) override { notifyAll(); }


	private:

		std::vector<MediaPtr> mMedia;

};
