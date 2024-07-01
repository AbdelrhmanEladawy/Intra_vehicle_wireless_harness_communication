#ifndef JSONREADER_H
#define JSONREADER_H

#include <QString>
#include <QObject>
#include <QtQml>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>

/**
 * @brief The jsonReader class provides methods to read and process data from a JSON file.
 */
class jsonReader : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructs a jsonReader object.
     *
     * @param FileLocation The location of the JSON file to read.
     * @param parent Pointer to the parent QObject.
     */
    explicit jsonReader(const QString &FileLocation, QObject *parent = nullptr);

    /**
     * @brief Destructor for the jsonReader object.
     */
    ~jsonReader();

    /**
     * @brief Gets the speed data from the JSON file.
     *
     * @return The speed data as a QString.
     */
    Q_INVOKABLE QString getDataSpeed();

    /**
     * @brief Gets the temperature data from the JSON file.
     *
     * @return The temperature data as a QString.
     */
    Q_INVOKABLE QString getDataTemperature();

    /**
     * @brief Gets the fuel state data from the JSON file.
     *
     * @return The fuel state data as a boolean.
     */
    Q_INVOKABLE bool getDataFuelState();

    /**
     * @brief Reads all data from the JSON file and updates the internal state.
     */
    Q_INVOKABLE void readAllData();

    /**
     * @brief Gets the state of the right arrow from the JSON file.
     *
     * @return The right arrow state as a boolean.
     */
    Q_INVOKABLE bool getRightArrowState();

    /**
     * @brief Gets the state of the left arrow from the JSON file.
     *
     * @return The left arrow state as a boolean.
     */
    Q_INVOKABLE bool getLeftArrowState();

    /**
     * @brief Switches the interval indicator state.
     */
    Q_INVOKABLE void switchIntervalIndicator();

    /**
     * @brief Gets the interval indicator state.
     *
     * @return The interval indicator state as a boolean.
     */
    Q_INVOKABLE bool getIntervalIndicator();

signals:
    /**
     * @brief Signal emitted when data is changed.
     */
    void DataChanged();

private:
    QFile file_object;              ///< The file object used for reading the JSON file.
    QJsonParseError jsonError;      ///< The JSON parse error.
    QJsonDocument jsonDocument;     ///< The JSON document object.
    QJsonObject jsonObj;            ///< The JSON object.
    QString DataSpeed;              ///< The speed data.
    QString DataTemperature;        ///< The temperature data.
    bool DataFuelState;             ///< The fuel state data.
    bool RightArrowState;           ///< The right arrow state data.
    bool LeftArrowState;            ///< The left arrow state data.
    bool intervalIndicator;         ///< The interval indicator state data.
};

#endif // JSONREADER_H
