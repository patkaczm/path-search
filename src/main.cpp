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

    auto view = engine.rootObjects()[0]->findChild<QObject*>("selectGridSizeView");
    auto spinBox = view->findChild<QObject*>("gridSize");
    qDebug() << "?" << spinBox->property("value");
    QObject::connect(spinBox, SIGNAL(valueModified()), backend, SLOT(onEvent1()));


    return app.exec();
}
