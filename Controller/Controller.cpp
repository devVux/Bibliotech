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
		pView->showEditForm(newBook, true);
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
        pView->showEditForm(newFilm, true);
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
        pView->showEditForm(newAlbum, true);
    });

    
    QObject::connect(pView.get(), &View::newMediaCreated, this, [this](const MediaPtr& media) {
        pModel->addMedia(media);
    });

    
    QObject::connect(pView.get(), &View::loadButtonClicked, this, [this](const QString& filepath) {
        XMLSerializer xml;
        xml.load(filepath, *pModel);
    });
    QObject::connect(pView.get(), &View::saveButtonClicked, this, [this](const QString& filepath) {
        XMLSerializer xml;
        xml.save(filepath, *pModel);
    });

    QObject::connect(pView.get(), &View::searchButtonClicked, this, [this](const QString& query) {
		pModel->search(query);

    });
    QObject::connect(pView.get(), &View::resetButtonClicked, this, [this]() {
		pModel->search("");
    });

    
    QObject::connect(pView.get(), &View::removeMedia, this, [this](const MediaPtr& media) {
        pModel->removeMedia(media);
    });
}
