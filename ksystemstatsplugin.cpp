#include "ksystemstatsplugin.h"

K_PLUGIN_CLASS_WITH_JSON(KSystemStatsPlugin, "metadata.json");

KSystemStatsPlugin::KSystemStatsPlugin(QObject *parent, const QVariantList &args)
    : KSysGuard::SensorPlugin(parent, args)
    , m_sensor_container(QStringLiteral("custom_sensor_container"), QStringLiteral("Custom Sensors"), this)
    , m_sensor_object(QStringLiteral("custom_sensor_object"), QStringLiteral("Sensors"), &m_sensor_container)
    , sensors()
    , filesToScan()

{
    createConfigIfNeeded();
    createSensorsFromConfig();
    addContainer(&m_sensor_container);
}

QFile *getFile()
{
    QString config_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.config/customsensorrc";
    QFile *file = new QFile(config_path);
    return file;
}

void KSystemStatsPlugin::createConfigIfNeeded()
{
    auto file = getFile();

    if (!file->exists()) {
        if (file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream out(file);
            out << "[Sensor]\nid=custom_sensor_1\nname=Custom Sensor 1\nfile=/tmp/custom_sensor_1.txt\nunit=UnitCelsius\n";
            out << "[Sensor]\nid=custom_sensor_2\nname=Custom Sensor 2\nfile=/tmp/custom_sensor_2.txt\nunit=UnitCelsius";
            file->close();
        }
    }

    delete file;
}

void KSystemStatsPlugin::createSensorsFromConfig()
{
    auto file = getFile();

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(file);

    QString text = in.readAll();
    auto sensors = text.split("[Sensor]\n");

    for (const QString &sensor : sensors) {
        if (!sensor.isEmpty())
            createSensor(sensor);
    }

    file->close();
    delete file;
}

void KSystemStatsPlugin::createSensor(QString sensorTxt)
{
    try {
        auto lines = sensorTxt.split("\n");

        auto idKeyValue = lines[0].split("=");
        auto nameKeyValue = lines[1].split("=");
        auto fileKeyValue = lines[2].split("=");
        auto unitKeyValue = lines[3].split("=");

        if (idKeyValue[0] != "id")
            return;
        if (nameKeyValue[0] != "name")
            return;
        if (fileKeyValue[0] != "file")
            return;
        if (unitKeyValue[0] != "unit")
            return;

        auto id = idKeyValue[1];
        auto name = nameKeyValue[1];
        auto file = fileKeyValue[1];
        auto unitTxt = unitKeyValue[1];

        auto metaEnum = QMetaEnum::fromType<KSysGuard::Unit>();
        int enumValue = metaEnum.keyToValue(unitTxt.toUtf8().constData());
        auto unit = static_cast<KSysGuard::Unit>(enumValue);

        auto sensor = QSharedPointer<KSysGuard::SensorProperty>::create(id, name, 0, &m_sensor_object);
        sensor->setUnit(unit);

        sensors.append(sensor);
        filesToScan.append(file);
    } catch (const std::exception &e) {
    }
}

void KSystemStatsPlugin::update()
{
    try {
        for (int i = 0; i < sensors.size(); ++i) {
            auto path = filesToScan[i];
            auto sensor = sensors[i];
            readFileAndUpdate(path, sensor);
        }
    } catch (const std::exception &e) {
    }
}

void KSystemStatsPlugin::readFileAndUpdate(const QString &path, QSharedPointer<KSysGuard::SensorProperty> sensor)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();

    bool ok;
    double value = line.toDouble(&ok);
    if (ok)
        sensor->setValue(value);

    file.close();
}

#include "ksystemstatsplugin.moc"
