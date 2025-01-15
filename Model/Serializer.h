#pragma once

#include <QtCore/QString>

#include "Biblioteca.h"

class Serializer {

	public:

		virtual bool save(const QString& filename, const Biblioteca& biblioteca) = 0;
		virtual bool load(const QString& filename, Biblioteca& biblioteca) const = 0;

};
