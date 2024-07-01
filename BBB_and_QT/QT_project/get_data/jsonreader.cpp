#include "jsonreader.h"

/**
 * @brief Constructs a jsonReader object.
 *
 * Initializes the jsonReader with the provided file location, default values for the data fields,
 * and checks if the file exists and is readable. If readable, it parses the JSON content.
 *
 * @param FileLocation The location of the JSON file to be read.
 * @param parent Pointer to the parent QObject.
 */
jsonReader::jsonReader(const QString &FileLocation, QObject *parent)
    : QObject{parent}
{
    DataSpeed = "00";
    DataTemperature = "25";
    DataFuelState = true;
    RightArrowState = false;
    LeftArrowState = false;
    intervalIndicator = false;

    file_object.setFileName(FileLocation);
    if(!file_object.exists())
    {
        qWarning() << "From constructor, the file doesn't exist: " << FileLocation;
    }
    else
    {
        if(file_object.open(QIODevice::ReadOnly))
        {
            QByteArray readedFile = file_object.readAll();
            file_object.close();

            jsonDocument = QJsonDocument::fromJson(readedFile, &jsonError);
            if(jsonError.error != QJsonParseError::NoError)
            {
                qWarning() << "JSON parse error: " << jsonError.errorString();
            }
        }
    }
}

/**
 * @brief Destructor for the jsonReader class.
 */
jsonReader::~jsonReader()
{
    // Cleanup code, if necessary
}

/**
 * @brief Gets the data speed.
 *
 * @return QString The current data speed.
 */
QString jsonReader::getDataSpeed()
{
    return DataSpeed;
}

/**
 * @brief Gets the data temperature.
 *
 * @return QString The current data temperature.
 */
QString jsonReader::getDataTemperature()
{
    return DataTemperature;
}

/**
 * @brief Gets the data fuel state.
 *
 * @return bool The current data fuel state.
 */
bool jsonReader::getDataFuelState()
{
    return DataFuelState;
}

/**
 * @brief Reads all data from the JSON file.
 *
 * This function opens the file, reads the JSON content, and updates the data fields accordingly.
 */
void jsonReader::readAllData()
{
    if(!file_object.open(QIODevice::ReadOnly))
    {
        qWarning() << "Error while opening the file: " << file_object.errorString();
    }
    else
    {
        QByteArray readedFile = file_object.readAll();
        file_object.close();
        jsonDocument = QJsonDocument::fromJson(readedFile, &jsonError);

        if(jsonDocument.isObject())
        {
            jsonObj = jsonDocument.object();
            DataSpeed = jsonObj["speed"].toString();
            DataTemperature = jsonObj["temperature"].toString();
            DataFuelState = jsonObj["fuel_states"].toBool();
            RightArrowState = jsonObj["right_arrow_state"].toBool();
            LeftArrowState = jsonObj["left_arrow_state"].toBool();
        }
    }

    emit DataChanged();
}

/**
 * @brief Gets the state of the right arrow.
 *
 * @return bool The current state of the right arrow.
 */
bool jsonReader::getRightArrowState()
{
    return RightArrowState;
}

/**
 * @brief Gets the state of the left arrow.
 *
 * @return bool The current state of the left arrow.
 */
bool jsonReader::getLeftArrowState()
{
    return LeftArrowState;
}

/**
 * @brief Switches the interval indicator state.
 *
 * Toggles the interval indicator between true and false.
 */
void jsonReader::switchIntervalIndicator()
{
    intervalIndicator = !intervalIndicator;
}

/**
 * @brief Gets the state of the interval indicator.
 *
 * @return bool The current state of the interval indicator.
 */
bool jsonReader::getIntervalIndicator()
{
    return intervalIndicator;
}
