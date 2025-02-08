#include "Controller.h"
#include "Book.h"
#include "Film.h"
#include "MusicAlbum.h"
#include "XMLSerializer.h"

void Controller::init() {
    
    QObject::connect(pView.get(), &View::addBookButtonClicked, this, [this]() {
        auto newBook = std::make_shared<Book>(
            "New Book",             
            "Default Publisher",    
            2000,                   
            "Unknown Author",       
            "No Plot"               
            );
        mQuery.clear(); // azzera il filtro
        pView->showEditForm(newBook, true);
        notifyAll();
    });

    
    QObject::connect(pView.get(), &View::addFilmButtonClicked, this, [this]() {
        auto newFilm = std::make_shared<Film>(
            "New Film",             
            "Default Publisher",    
            2000,                    
            "Unknown Director",     // REGISTA
            "No Plot",              //TRAMA
            90                      
            );
        mQuery.clear();
        pView->showEditForm(newFilm, true);
        notifyAll();
    });

    
    QObject::connect(pView.get(), &View::addMusicAlbumButtonClicked, this, [this]() {
        auto newAlbum = std::make_shared<MusicAlbum>(
            "New Album",            
            "Default Publisher",    
            2000,                   
            "Unknown Artist",       
            "Pop",                  // Genere
            10                      
            );
        mQuery.clear();
        pView->showEditForm(newAlbum, true);
        notifyAll();
    });

    
    QObject::connect(pView.get(), &View::newMediaCreated, this, [this](const MediaPtr& media) {
        pModel->addMedia(media);
        notifyAll();
    });

    
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

    // Quando viene emesso il segnale searchButtonClicked, il Controller aggiorna mQuery e chiama notifyAll()
    QObject::connect(pView.get(), &View::searchButtonClicked, this, [this](const QString& query) {
        mQuery = query;
        notifyAll();
    });
    // Il tasto reset cancella mQuery e chiama notifyAll()
    QObject::connect(pView.get(), &View::resetButtonClicked, this, [this]() {
        mQuery.clear();
        notifyAll();
    });

    
    QObject::connect(pView.get(), &View::removeMedia, this, [this](const MediaPtr& media) {
        pModel->removeMedia(media);
        notifyAll();
    });
}
