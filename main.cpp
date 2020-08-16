#include <QCoreApplication>
#include <QSensor>
#include <QSensorManager>
#include <QDebug>
// export UBUNTU_PLATFORM_API_BACKEND=touch_mirserver


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList _availableSensors;
    foreach (const QByteArray &type, QSensor::sensorTypes()) {
        qDebug() << "Found type" << type;
        foreach (const QByteArray &identifier, QSensor::sensorsForType(type)) {
            qDebug() << "Found identifier" << identifier;
            // Don't put in sensors we can't connect to
            QSensor* sensor = new QSensor(type, &a);
            sensor->setIdentifier(identifier);
            if (!sensor->connectToBackend()) {
                qDebug() << "Couldn't connect to" << identifier;
                continue;
            }

            qDebug() << "Adding identifier" << identifier;
            _availableSensors.append(identifier);
        }
    }
    qDebug();
    qDebug() << "<<<<<<<<<<<<<<<<<< Available sensors:";
    qDebug() << _availableSensors;
    qDebug() << "<<<<<<<<<<<<<<<<<<";
    //qApp->quit();
    return 0;
}
