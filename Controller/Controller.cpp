#include "Controller.h"
#include "Book.h"
#include "Film.h"
#include "MusicAlbum.h"
#include "XMLSerializer.h"

void Controller::init() {
    // Collegamento per "Add Book"
    QObject::connect(pView.get(), &View::addBookButtonClicked, this, [this]() {
         auto newBook = std::make_shared<Book>(
             "New Book", "Default Publisher", 2000, "Unknown Author", "No Plot"
         );
         mQuery.clear();
         pView->showEditForm(newBook, true);
         notifyAllObservers();
    });

    // Collegamento per "Add Film"
    QObject::connect(pView.get(), &View::addFilmButtonClicked, this, [this]() {
         auto newFilm = std::make_shared<Film>(
             "New Film", "Default Publisher", 2000, "Unknown Director", "No Plot", 90
         );
         mQuery.clear();
         pView->showEditForm(newFilm, true);
         notifyAllObservers();
    });

    // Collegamento per "Add Music Album"
    QObject::connect(pView.get(), &View::addMusicAlbumButtonClicked, this, [this]() {
         auto newAlbum = std::make_shared<MusicAlbum>(
             "New Album", "Default Publisher", 2000, "Unknown Artist", "Pop", 10
         );
         mQuery.clear();
         pView->showEditForm(newAlbum, true);
         notifyAllObservers();
    });
    
    // Collegamento per la notifica dopo Save (creazione o modifica)
    QObject::connect(pView.get(), &View::newMediaCreated, this, [this](const MediaPtr& media) {
         pModel->addMedia(media);
         notifyAllObservers();
    });
    
    // Caricamento e salvataggio
    QObject::connect(pView.get(), &View::loadButtonClicked, this, [this](const QString& filepath) {
        XMLSerializer xml;
        xml.load(filepath, *pModel);
        mQuery.clear();
        notifyAllObservers();
    });
    QObject::connect(pView.get(), &View::saveButtonClicked, this, [this](const QString& filepath) {
        XMLSerializer xml;
        xml.save(filepath, *pModel);
    });
    
    // Ricerca
    QObject::connect(pView.get(), &View::searchButtonClicked, this, [this](const QString& query) {
        mQuery = query;
        notifyAllObservers();
    });
    QObject::connect(pView.get(), &View::resetButtonClicked, this, [this]() {
        mQuery.clear();
        notifyAllObservers();
    });
    
    // Rimozione di un media
    QObject::connect(pView.get(), &View::removeMedia, this, [this](const MediaPtr& media) {
        pModel->removeMedia(media);
        notifyAllObservers();
    });
}
