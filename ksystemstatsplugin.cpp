#include "ksystemstatsplugin.h"


K_PLUGIN_CLASS_WITH_JSON(KSystemStatsPlugin, "metadata.json");

QString file1 = QStringLiteral("/tmp/custom_sensor_1.txt");
QString file2 = QStringLiteral("/tmp/custom_sensor_2.txt");
QString file3 = QStringLiteral("/tmp/custom_sensor_3.txt");
QString file4 = QStringLiteral("/tmp/custom_sensor_4.txt");
QString file5 = QStringLiteral("/tmp/custom_sensor_5.txt");

KSystemStatsPlugin::KSystemStatsPlugin(QObject *parent, const QVariantList &args)
    : KSysGuard::SensorPlugin(parent, args),
    m_sensor_container(QStringLiteral("custom_sensor_container"),QStringLiteral("Custom Container"), this),
    m_sensor_object(QStringLiteral("custom_sensor_object"),  QStringLiteral("Custom Sensor Object"), &m_sensor_container),
    m_custom_sensor_1(QStringLiteral("custom_sensor_1"), QStringLiteral("Custom Sensor 1"), QVariant(0), &m_sensor_object),
    m_custom_sensor_2(QStringLiteral("custom_sensor_2"), QStringLiteral("Custom Sensor 2"), QVariant(0), &m_sensor_object),
    m_custom_sensor_3(QStringLiteral("custom_sensor_3"), QStringLiteral("Custom Sensor 3"), QVariant(0), &m_sensor_object),
    m_custom_sensor_4(QStringLiteral("custom_sensor_4"), QStringLiteral("Custom Sensor 4"), QVariant(0), &m_sensor_object),
    m_custom_sensor_5(QStringLiteral("custom_sensor_5"), QStringLiteral("Custom Sensor 5"), QVariant(0), &m_sensor_object)
{
    m_custom_sensor_1.setUnit(KSysGuard::UnitCelsius);
    m_custom_sensor_2.setUnit(KSysGuard::UnitCelsius);
    m_custom_sensor_3.setUnit(KSysGuard::UnitCelsius);
    m_custom_sensor_4.setUnit(KSysGuard::UnitCelsius);
    m_custom_sensor_5.setUnit(KSysGuard::UnitCelsius);
    addContainer(&m_sensor_container);
}


void KSystemStatsPlugin::update()
{
    readFileAndUpdate(file1, m_custom_sensor_1);
    readFileAndUpdate(file2, m_custom_sensor_2);
    readFileAndUpdate(file3, m_custom_sensor_3);
    readFileAndUpdate(file4, m_custom_sensor_4);
    readFileAndUpdate(file5, m_custom_sensor_5);

}

void KSystemStatsPlugin::readFileAndUpdate(const QString &path,  KSysGuard::SensorProperty &sensor)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  return;

    QTextStream in(&file);
    QString line = in.readLine();

    bool ok;
    double value = line.toDouble(&ok);
    if (ok)  sensor.setValue(value);

    file.close();
}


#include "ksystemstatsplugin.moc"
