#include "Controller.h"
#include "Book.h"
#include "Film.h"
#include "MusicAlbum.h"
#include "XMLSerializer.h"

void Controller::init() {

    // Collegamento per "Add Book" con valori di default (placeholder)
    QObject::connect(pView.get(), &View::addBookButtonClicked, this, [this]() {
         auto newBook = std::make_shared<Book>(
             "New Book",             // Titolo di default
             "Default Publisher",    // Publisher di default
             2000,                   // Anno di default
             "Unknown Author",       // Autore di default
             "No Plot"               // Trama di default
         );
         mQuery.clear();
         pView->showEditForm(newBook, true);
         notifyAll();
    });

    // Collegamento per "Add Film"
    QObject::connect(pView.get(), &View::addFilmButtonClicked, this, [this]() {
         auto newFilm = std::make_shared<Film>(
             "New Film",             // Titolo di default
             "Default Publisher",    // Publisher di default
             2000,                   // Anno di default
             "Unknown Director",     // Regista di default
             "No Plot",              // Trama di default
             90                      // Durata di default (in minuti)
         );
         mQuery.clear();
         pView->showEditForm(newFilm, true);
         notifyAll();
    });

    // Collegamento per "Add Music Album"
    QObject::connect(pView.get(), &View::addMusicAlbumButtonClicked, this, [this]() {
         auto newAlbum = std::make_shared<MusicAlbum>(
             "New Album",            // Titolo di default
             "Default Publisher",    // Publisher di default
             2000,                   // Anno di default
             "Unknown Artist",       // Artista di default
             "Pop",                  // Genere di default
             10                      // Numero di tracce di default
         );
         mQuery.clear();
         pView->showEditForm(newAlbum, true);
         notifyAll();
    });
    
    // Quando il form di creazione viene completato (premendo Save)
    QObject::connect(pView.get(), &View::newMediaCreated, this, [this](const MediaPtr& media) {
         pModel->addMedia(media);
         notifyAll();
    });
    
    // Caricamento e salvataggio
    QObject::connect(pView.get(), &View::loadButtonClicked, this, [this](const QString& filepath) {
        XMLSerializer xml;
        xml.load(filepath, *pModel);
        mQuery.clear();
        notifyAll();
    });
    QObject::connect(pView.get(), &View::saveButtonClicked, this, [this](const QString& filepath) {
        XMLSerializer xml;
        xml.save(filepath, *pModel);
    });
    
    // Collegamenti per la ricerca
    QObject::connect(pView.get(), &View::searchButtonClicked, this, [this](const QString& query) {
        mQuery = query;
        notifyAll();
    });
    QObject::connect(pView.get(), &View::resetButtonClicked, this, [this]() {
        mQuery.clear();
        notifyAll();
    });
    
    // Rimozione di un media
    QObject::connect(pView.get(), &View::removeMedia, this, [this](const MediaPtr& media) {
        pModel->removeMedia(media);
        notifyAll();
    });
}
