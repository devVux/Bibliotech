#pragma once

#include "Media.h"

class Film: public Media {

	public:

		Film(const QString& title, const QString& publisher, uint32_t year, const QString& director, const QString& plot, uint32_t duration):
			Media(title, publisher, year), mDirector(director), mPlot(plot),  mDuration(duration) {
		};

        virtual void accept(Visitor* visitor) override;

        virtual bool mathes(const QString& s) const override;


		void director(const QString& director) { mDirector = director; mDirty = true; }
		void plot(const QString& plot) { mPlot = plot; mDirty = true; }
		void duration(uint32_t duration) { mDuration = duration; mDirty = true; }

		const QString& director() const { return mDirector; }
		const QString& plot() const { return mPlot; }
		uint32_t duration() const { return mDuration; }

	private:

		QString mDirector;
		QString mPlot;
		uint32_t mDuration;

};
