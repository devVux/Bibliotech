#pragma once

#include "Serializer.h"
#include "XMLVisitor.h"

class XMLSerializer: public Serializer {

	public:

		bool save(const QString& filename, const Biblioteca& biblioteca) override;
		bool load(const QString& filename, Biblioteca& biblioteca) const override;


	private:
		
		XMLVisitor mVisitor;

};