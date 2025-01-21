#include "Controller.h"

#include "Book.h"
#include "Film.h"
#include "MusicAlbum.h"
#include "XMLSerializer.h"

void Controller::init() {

    // TODO: set reasonable default media values
	QObject::connect(pView.get(), &View::addBookButtonClicked, this, [this]() {
		pModel->addMedia(std::make_shared<Book>("Title", "Publisher", 2020, "Author", "Plot"));
	});
    QObject::connect(pView.get(), &View::addFilmButtonClicked, this, [this]() {
        pModel->addMedia(std::make_shared<Film>("Title", "Publisher", 2020, "Author", "Plot", 1));
    });
    QObject::connect(pView.get(), &View::addMusicAlbumButtonClicked, this, [this](){
    pModel->addMedia(std::make_shared<MusicAlbum>("RockStar","Publisher",2018,"Sfera","Trap",11  ));});



    QObject::connect(pView.get(), &View::loadButtonClicked, this, [this](const QString& filepath) {
		XMLSerializer xml;
		xml.load(filepath, *pModel);
    });
    QObject::connect(pView.get(), &View::saveButtonClicked, this, [this](const QString& filepath) {
		XMLSerializer xml;
		xml.save(filepath, *pModel);
    });
	
		
	QObject::connect(pView.get(), &View::searchButtonClicked, this, [this](const QString& query) {
		mQuery = query;
        notifyAll();
	});
	QObject::connect(pView.get(), &View::resetButtonClicked, this, [this]() {
		mQuery.clear();
        notifyAll();
	});


	QObject::connect(pView.get(), &View::removeMedia, this, [this](const MediaPtr& media) {
		pModel->removeMedia(media);
        notifyAll();
	});


}
