#pragma once

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QQmlApplicationEngine& engine, QObject *parent = nullptr);

signals:
    void userNameChanged();

public slots:
    void onEvent();
    void onEvent1();
    void changeColor();

private:
    QQmlApplicationEngine& mEngine;
    QTimer mTimer;
};

