#include "Backend.hpp"

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QQuickItem>
#include <QQuickAsyncImageProvider>

Backend::Backend(QQmlApplicationEngine& engine, QObject *parent)
    : QObject(parent)
    , mEngine(engine)
{
    auto gridView = mEngine.rootObjects()[0]->findChild<QQuickItem*>("gridView");
//    QObject::connect(gridView, &QQuickItem::visibleChanged, this, &Backend::onEvent);
}

void Backend::onEvent() {
    qInfo() << "Called from onEvent\n";
    QObject::connect(&mTimer, &QTimer::timeout, this, &Backend::changeColor);
    mTimer.start(1000);
}


void Backend::onEvent1() {
    qInfo() << "Called from onEvent1\n";
    auto view = mEngine.rootObjects()[0]->findChild<QObject*>("selectGridSizeView");
    auto spinBox = view->findChild<QObject*>("gridSize");
    qDebug() << "?" << spinBox->property("value");
}

void Backend::changeColor()
{
    qDebug() << "changeColor";
    auto gridView = mEngine.rootObjects()[0]->findChild<QQuickItem*>("gridView");
    auto r1 = gridView->findChild<QQuickItem*>("r1");
    qDebug() << r1;
    if (r1->property("color") == "red") {
        r1->setProperty("color", "blue");
    } else {
        r1->setProperty("color", "red");
    }
}
