#pragma once

#include <ksysguard/systemstats/SensorPlugin.h>
#include <ksysguard/systemstats/SensorContainer.h>
#include <ksysguard/systemstats/SensorObject.h>
#include <ksysguard/systemstats/SensorProperty.h>

#include <KPluginFactory>
#include <QObject>
#include <QFile>
#include <QTextStream>


class KSystemStatsPlugin : public KSysGuard::SensorPlugin
{
    Q_OBJECT

public:
    explicit KSystemStatsPlugin(QObject *parent = nullptr, const QVariantList &args = QVariantList());

    ~KSystemStatsPlugin() override = default;

    void update() override;
    void readFileAndUpdate(const QString &path, KSysGuard::SensorProperty &sensor);

private:
    KSysGuard::SensorContainer m_sensor_container;
    KSysGuard::SensorObject m_sensor_object;
    KSysGuard::SensorProperty m_custom_sensor_1;
    KSysGuard::SensorProperty m_custom_sensor_2;
    KSysGuard::SensorProperty m_custom_sensor_3;
    KSysGuard::SensorProperty m_custom_sensor_4;
    KSysGuard::SensorProperty m_custom_sensor_5;
};
