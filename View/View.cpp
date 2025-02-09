#include "View.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QIcon>
#include <QTimer>
#include <QSizePolicy>
#include <QDebug>

#include <QtVisitor.h>
#include <FormVisitor.h>

void View::init() {
    // Creazione della toolbar
    auto toolbar = new QToolBar(this);
   
    toolbar->setIconSize(QSize(48, 48));
    
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    
    QAction* loadAction = toolbar->addAction(QIcon(":/icons/load.svg"), "Load");
    QAction* saveAction = toolbar->addAction(QIcon(":/icons/save.svg"), "Save");
    QAction* addBookAction = toolbar->addAction(QIcon(":/icons/book.svg"), "Add Book");
    QAction* addFilmAction = toolbar->addAction(QIcon(":/icons/film.svg"), "Add Film");
    QAction* addMusicAlbumAction = toolbar->addAction(QIcon(":/icons/music.svg"), "Add Music Album");

    
    connect(addBookAction, &QAction::triggered, this, [this]() {
        
        emit addBookButtonClicked();
    });
    connect(addFilmAction, &QAction::triggered, this, [this]() {
        
        emit addFilmButtonClicked();
    });
    connect(addMusicAlbumAction, &QAction::triggered, this, [this]() {
        
        emit addMusicAlbumButtonClicked();
    });

    
    connect(loadAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Load File", "dump.xml", "XML Files (*.xml);;All Files (*)");
        if (!filePath.isEmpty()) {
           
            emit loadButtonClicked(filePath);
        }
    });
    connect(saveAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "XML Files (*.xml);;All Files (*)");
        if (!filePath.isEmpty()) {
           
            emit saveButtonClicked(filePath);
        }
    });

    addToolBar(toolbar);

    
    QTimer::singleShot(0, [toolbar]() {
        for (QAction* action : toolbar->actions()) {
            QWidget* widget = toolbar->widgetForAction(action);
            if (widget) {
                widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                
            }
        }
    });

    
    listPage = new QWidget(this);
    QVBoxLayout* listLayout = new QVBoxLayout(listPage);

    //ricerca vincolo 14
    QWidget* searchWidget = new QWidget(listPage);
    QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);
    searchBar = new QLineEdit(searchWidget);
    searchBar->setPlaceholderText("Search...");
    resetButton = new QPushButton("Reset", searchWidget);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(resetButton);
    searchWidget->setLayout(searchLayout);
    listLayout->addWidget(searchWidget);

    
    scrollArea = new QScrollArea(listPage);
    mediaContainer = new QWidget();
    QVBoxLayout* mediaLayout = new QVBoxLayout(mediaContainer);
    mediaContainer->setLayout(mediaLayout);
    scrollArea->setWidget(mediaContainer);
    scrollArea->setWidgetResizable(true);
    listLayout->addWidget(scrollArea);

    listPage->setLayout(listLayout);

    stackWidget = new QStackedWidget(this);
    stackWidget->addWidget(listPage);
    setCentralWidget(stackWidget);

    
    connect(searchBar, &QLineEdit::textChanged, this, [this](const QString &text) {
        
        emit searchButtonClicked(text);
    });
    connect(resetButton, &QPushButton::clicked, this, [this]() {
        
        searchBar->clear();
        emit resetButtonClicked();
    });
}

void View::update(void* data) {
    QString filter;
    if (data)
        filter = *static_cast<QString*>(data);
    
    display(pModel->search(filter));
}

void View::display(const std::vector<MediaPtr>& medias) {
    QLayout* layout = mediaContainer->layout();
    if (!layout) {
        layout = new QVBoxLayout(mediaContainer);
        mediaContainer->setLayout(layout);
    }
    clearLayout(layout);

    QtVisitor visitor(listPage);
    for (const MediaPtr& media : medias) {
        media->accept(&visitor);
        auto w = visitor.widget();
        if (!w) {
            
            continue;
        }

        
        connect(w, &MediaWidget::deleteButtonClicked, this, [this, media]() {
            
            emit removeMedia(media);
        });

        
        connect(w, &MediaWidget::editButtonClicked, this, [this, media]() {
            
            showEditForm(media, false);
        });

        layout->addWidget(w);
    }
}

void View::showEditForm(const MediaPtr& media, bool isNew) {
    auto* formVisitor = new FormVisitor(listPage);
    formVisitor->onFinish = [this, media, isNew, formVisitor](QWidget* formWidget) {
        bool wasSaved = formVisitor->saved;
        
        stackWidget->setCurrentWidget(listPage);
        stackWidget->removeWidget(formWidget);
        formWidget->deleteLater();
        if (wasSaved) {
            if (isNew) {
                emit newMediaCreated(media);
            } else {
                //Forziamo un agg
                emit searchButtonClicked(searchBar->text());
            }
        }
        delete formVisitor;
    };
    media->accept(formVisitor);
    QWidget* formWidget = formVisitor->widget();
    if (!formWidget) {
        
        delete formVisitor;
        return;
    }
    stackWidget->addWidget(formWidget);
    stackWidget->setCurrentWidget(formWidget);
}

void View::clearLayout(QLayout* layout) {
    if (!layout)
        return;
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (item->widget())
            delete item->widget();
        delete item;
    }
}
