#pragma once

#include <QtWidgets/QWidget>
#include "Visitor.h"
#include <functional>

class FormVisitor: public Visitor {
public:
    FormVisitor(QWidget* parent)
        : pParent(parent)
        , pFormWidget(nullptr)
        , saved(false)
        , onFinish(nullptr)
    { }

    virtual ~FormVisitor() { }

    virtual void visit(Film& film) override;
    virtual void visit(Book& book) override;
    virtual void visit(MusicAlbum& album) override;

    QWidget* widget() const { return pFormWidget; }

    std::function<void(QWidget*)> onFinish;
    bool saved;

private:
    QWidget* pParent;
    QWidget* pFormWidget;
};
