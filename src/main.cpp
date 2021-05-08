#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQuickControls2/QtQuickControls2>

#include "Backend/Backend.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QString("qrc:/view/main.qml")));

    Backend* backend = new Backend(engine, &app);

    QObject* view = engine.rootObjects()[0]->findChild<QObject*>("gridView");

    auto gridCells = view->property("gridCells");

    QObject::connect(view, SIGNAL(startPathSearching(QVariant, int)),
                     backend, SLOT(onStartPathFinding(QVariant, int)));
    QObject::connect(backend, SIGNAL(pathFindingDone(QVariant)),
                     view, SLOT(onPathFindingDone(QVariant)));
    QObject::connect(backend, SIGNAL(vertexVisited(QVariant)),
                     view, SLOT(onVertexVisited(QVariant)));


    return app.exec();
}
