TEMPLATE = app
TARGET = Bibliotech
CONFIG += c++17

QT += core gui widgets xml

SOURCES += \
    main.cpp \
    Model/Book.cpp \
    Model/Film.cpp \
    Model/MusicAlbum.cpp\
    Model/Biblioteca.cpp \
    Model/Serializers/XMLSerializer.cpp \
    Model/Serializers/XMLVisitor.cpp \
    View/QtVisitor.cpp \
    View/FormVisitor.cpp \
    View/View.cpp \
    Controller/Controller.cpp


HEADERS += \
    Model/Media.h \
    Model/Book.h \
    Model/Film.h \
    Model/MusicAlbum.h\
    Model/Biblioteca.h \
    Model/Observer.h \
    Model/Serializer.h \
    Model/Visitor.h \
    Model/Serializers/XMLSerializer.h \
    Model/Serializers/XMLVisitor.h \
    View/QtVisitor.h \
    View/FormVisitor.h \
    View/View.h \
    View\MediaWidget.h \
    Controller/Controller.h



INCLUDEPATH += \
    Model \
    Controller \
    View \
    Model/Serializers

QMAKE_CXXFLAGS += -Wall -Wextra

DESTDIR = bin

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
