#pragma once

#include "Observer.h"
#include <memory>
#include <QtCore/QString>

class Visitor;
class Media;

using MediaPtr = std::shared_ptr<Media>;

class Media: public SubjectNoParameters {

	public:

		Media(const QString &title, const QString &publisher, uint32_t year): 
			mTitle(title), mPublisher(publisher), mYear(year) {}
		virtual ~Media() = default;

        virtual void accept(Visitor* visitor) = 0;
		virtual bool mathes(const QString &s) const = 0;


		void title(const QString& title) { mTitle = title; mDirty = true;  }
		void publisher(const QString& publisher) { mPublisher = publisher; mDirty = true; }
		void year(uint32_t year) { mYear = year; mDirty = true; }

		const QString& title() const { return mTitle; }
		const QString& publisher() const { return mPublisher; }
		uint32_t year() const { return mYear; }


		void commitChanges() { 
			if (mDirty) {
				notifyAll();
				mDirty = false;
			}
		}


	protected:
		
		QString mTitle;
		QString mPublisher;
		uint32_t mYear;

		// Flag to check if the media has been modified and reduce the number of notifications
		bool mDirty { false };	

};
