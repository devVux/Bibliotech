#pragma once

#include "Biblioteca.h"
#include "Observer.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <memory>

class View : public QMainWindow, public Observer {
    Q_OBJECT
public:
    View(ModelPtr model)
        : pModel(model), listPage(new QWidget(this))
    { }

    void init();
    // Override dell'interfaccia Observer
    virtual void update() override;
    void display(const std::vector<MediaPtr>& medias);
    void showEditForm(const MediaPtr& media, bool isNew);

signals:
    void addBookButtonClicked();
    void addFilmButtonClicked();
    void addMusicAlbumButtonClicked();

    void saveButtonClicked(const QString& path);
    void loadButtonClicked(const QString& path);

    void searchButtonClicked(const QString& query);
    void resetButtonClicked();

    void removeMedia(const MediaPtr& media);
    void newMediaCreated(const MediaPtr& media);

private:
    void clearLayout(class QLayout* layout);

private:
    ModelPtr pModel;
    QStackedWidget* stackWidget { nullptr };

    // Pagina della list view
    QWidget* listPage { nullptr };
    QLineEdit* searchBar { nullptr };
    QPushButton* resetButton { nullptr };
    QScrollArea* scrollArea { nullptr };
    QWidget* mediaContainer { nullptr };
};
