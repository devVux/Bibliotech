#pragma once

#include "Media.h"

class Book: public Media {

	public:

		Book(const QString& title, const QString& publisher, uint32_t year, const QString& author, const QString& plot):
			Media(title, publisher, year), mAuthor(author), mPlot(plot) { }


        virtual void accept(Visitor* visitor) override;

        virtual bool mathes(const QString& s) const override;


		void author(const QString& author) { mAuthor = author; mDirty = true; }
		void plot(const QString& plot) { mPlot = plot; mDirty = true; }

		const QString& author() const { return mAuthor; }
		const QString& plot() const { return mPlot; }


	private:

		QString mAuthor;
		QString mPlot;

};
