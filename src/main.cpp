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

    //path finding

    QObject* pathFindingWindow = engine.rootObjects().at(0)->findChild<QObject*>("pathFindingWindow");

    QObject::connect(pathFindingWindow, SIGNAL(startPathFinding(QVariant,int)),
                     backend, SLOT(onStartPathFinding(QVariant,int)));
    QObject::connect(backend, SIGNAL(pathFindingDone(QVariant)),
                     pathFindingWindow, SLOT(onPathFindingDone(QVariant)));

    QObject::connect(backend, SIGNAL(vertexVisited(QVariant)),
                     pathFindingWindow, SLOT(onCellVisited(QVariant)));

    QObject::connect(backend, SIGNAL(availableAlgorithmsSet(QVariant)),
                     pathFindingWindow->findChild<QObject*>("availableAlgorithms"), SLOT(onAvailableAlgorithmsSet(QVariant)));
    QObject::connect(pathFindingWindow->findChild<QObject*>("availableAlgorithms"), SIGNAL(algorithmSelected(QVariant)),
                     backend, SLOT(onAlgorithmSelected(QVariant)));

    //maze generation

    QObject* mazeGenerationWindow = engine.rootObjects().at(0)->findChild<QObject*>("mazeGenerationWindow");

    QObject::connect(mazeGenerationWindow, SIGNAL(generateMaze(int, int)),
                     backend, SLOT(onGenerateMaze(int, int)));

    QObject::connect(backend, SIGNAL(mazeGenerationDone(QVariant)),
                     mazeGenerationWindow, SLOT(onMazeGenerationDone(QVariant)));

//    QObject::connect(backend, SIGNAL(mazeCellGenerated(QVariant)),
//                     view, SLOT(onMazeCellGenerated(QVariant)));

    backend->loadAlgorithms();

    return app.exec();
}
