#include "file_reader.h"

/**
 * @brief Constructs a fileReader object.
 *
 * Initializes the fileReader with the provided file location and checks if the file exists.
 *
 * @param FileLocation The location of the file to be read.
 * @param parent Pointer to the parent QObject.
 */
fileReader::fileReader(const QString &FileLocation, QObject *parent)
    : QObject{parent}
{
    file_object.setFileName(FileLocation);
    if(!file_object.exists())
    {
        qWarning() << "The file doesn't exist: " << FileLocation;
    }
}

/**
 * @brief Destructor for the fileReader class.
 */
fileReader::~fileReader()
{
    // Cleanup code, if necessary
}

/**
 * @brief Gets the data speed.
 *
 * @return QString The current data speed.
 */
QString fileReader::getDataSpeed()
{
    return DataSpeed;
}

/**
 * @brief Gets the data fuel state.
 *
 * @return bool The current data fuel state.
 */
bool fileReader::getDataFuelState()
{
    return DataFuelState;
}

/**
 * @brief Reads all data from the file.
 *
 * This function opens the file, reads the data speed and fuel state, and then emits a signal indicating that the data has changed.
 */
void fileReader::readAllData()
{
    if(!file_object.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qWarning() << "Error while opening the file: " << file_object.errorString();
        return;
    }

    file_object.seek(0);
    QTextStream fileStream(&file_object);

    // Read data speed
    QString data = fileStream.readLine();
    DataSpeed = data;

    // Read data fuel state
    data = fileStream.readLine();
    DataFuelState = QVariant(data).toBool();

    qInfo() << "DataSpeed:" << DataSpeed << "DataFuelState:" << DataFuelState;

    emit DataChanged();

    file_object.close();
}
