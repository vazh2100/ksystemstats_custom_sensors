#pragma once

#include <stdexcept>

#include <ksysguard/systemstats/SensorContainer.h>
#include <ksysguard/systemstats/SensorObject.h>
#include <ksysguard/systemstats/SensorPlugin.h>
#include <ksysguard/systemstats/SensorProperty.h>

#include <KPluginFactory>
#include <QDir>
#include <QFile>
#include <QMetaEnum>
#include <QObject>
#include <QStandardPaths>
#include <QTextStream>

class KSystemStatsPlugin : public KSysGuard::SensorPlugin
{
    Q_OBJECT

public:
    explicit KSystemStatsPlugin(QObject *parent = nullptr, const QVariantList &args = QVariantList());

    ~KSystemStatsPlugin() override = default;

    void update() override;

private:
    KSysGuard::SensorContainer m_sensor_container;
    KSysGuard::SensorObject m_sensor_object;
    QList<QSharedPointer<KSysGuard::SensorProperty>> sensors;
    QList<QString> filesToScan;
    void createConfigIfNeeded();
    void createSensorsFromConfig();
    void createSensor(QString sensor);
    void readFileAndUpdate(const QString &path, QSharedPointer<KSysGuard::SensorProperty> sensor);
};
