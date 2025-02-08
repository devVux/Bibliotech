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
        qDebug() << "Add Book triggered";
        emit addBookButtonClicked();
    });
    connect(addFilmAction, &QAction::triggered, this, [this]() {
        qDebug() << "Add Film triggered";
        emit addFilmButtonClicked();
    });
    connect(addMusicAlbumAction, &QAction::triggered, this, [this]() {
        qDebug() << "Add Music Album triggered";
        emit addMusicAlbumButtonClicked();
    });
    connect(loadAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Load File", "dump.xml", "XML Files (*.xml);;All Files (*)");
        if (!filePath.isEmpty()) {
            qDebug() << "Load triggered:" << filePath;
            emit loadButtonClicked(filePath);
        }
    });
    connect(saveAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "XML Files (*.xml);;All Files (*)");
        if (!filePath.isEmpty()) {
            qDebug() << "Save triggered:" << filePath;
            emit saveButtonClicked(filePath);
        }
    });

    addToolBar(toolbar);

    // Imposta la SizePolicy dei pulsanti della toolbar dopo la creazione completa
    QTimer::singleShot(0, [toolbar]() {
        for (QAction* action : toolbar->actions()) {
            QWidget* widget = toolbar->widgetForAction(action);
            if (widget) {
                widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                qDebug() << "Set size policy for widget:" << widget;
            }
        }
    });

    // Costruzione della pagina di list view
    listPage = new QWidget(this);
    QVBoxLayout* listLayout = new QVBoxLayout(listPage);

    // Creazione del widget di ricerca
    QWidget* searchWidget = new QWidget(listPage);
    QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);
    searchBar = new QLineEdit(searchWidget);
    searchBar->setPlaceholderText("Search...");
    resetButton = new QPushButton("Reset", searchWidget);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(resetButton);
    searchWidget->setLayout(searchLayout);
    listLayout->addWidget(searchWidget);

    // Creazione dello scroll area per la lista dei media
    scrollArea = new QScrollArea(listPage);
    mediaContainer = new QWidget();
    QVBoxLayout* mediaLayout = new QVBoxLayout(mediaContainer);
    mediaContainer->setLayout(mediaLayout);
    scrollArea->setWidget(mediaContainer);
    scrollArea->setWidgetResizable(true);
    listLayout->addWidget(scrollArea);

    listPage->setLayout(listLayout);

    // Creazione dello stack widget: la list view viene inserita per prima
    stackWidget = new QStackedWidget(this);
    stackWidget->addWidget(listPage);
    setCentralWidget(stackWidget);

    // Connessioni per la barra di ricerca e il pulsante reset
    connect(searchBar, &QLineEdit::textChanged, this, [this](const QString &text) {
        qDebug() << "Search text changed:" << text;
        emit searchButtonClicked(text);
    });
    connect(resetButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Reset pressed";
        searchBar->clear();
        emit resetButtonClicked();
    });
}

void View::update() {
    // Usiamo il testo corrente della searchBar come filtro; se è vuoto, mostra tutti gli elementi
    QString filter = (searchBar) ? searchBar->text() : "";
    qDebug() << "View::update called with filter:" << filter;
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
            qDebug() << "Warning: visitor.widget() returned null";
            continue;
        }

        connect(w, &MediaWidget::deleteButtonClicked, this, [this, media]() {
            qDebug() << "Delete clicked";
            emit removeMedia(media);
        });

        connect(w, &MediaWidget::editButtonClicked, this, [this, media]() {
            qDebug() << "Edit clicked";
            showEditForm(media, false);
        });

        layout->addWidget(w);
    }
}

void View::showEditForm(const MediaPtr& media, bool isNew) {
    auto* formVisitor = new FormVisitor(listPage);
    formVisitor->onFinish = [this, media, isNew, formVisitor](QWidget* formWidget) {
        bool wasSaved = formVisitor->saved;
        qDebug() << "onFinish called, wasSaved:" << wasSaved;
        stackWidget->setCurrentWidget(listPage);
        stackWidget->removeWidget(formWidget);
        formWidget->deleteLater();
        if (wasSaved) {
            if (isNew) {
                emit newMediaCreated(media);
            } else {
                // Per ripristinare la visualizzazione completa dopo la modifica, azzeriamo il filtro
                searchBar->clear();
                emit resetButtonClicked();
            }
        }
        delete formVisitor;
    };
    media->accept(formVisitor);
    QWidget* formWidget = formVisitor->widget();
    if (!formWidget) {
        qDebug() << "Error: formVisitor->widget() returned null";
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
