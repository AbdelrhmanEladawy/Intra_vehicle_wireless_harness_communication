#ifndef FILE_READER_H
#define FILE_READER_H

#include <QObject>
#include <QtQml>
#include <QFile>
#include <QTextStream>
#include <QtDebug>

/**
 * @brief The fileReader class provides methods to read and process data from a file.
 */
class fileReader : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a fileReader object.
     *
     * @param FileLocation The location of the file to read.
     * @param parent Pointer to the parent QObject.
     */
    explicit fileReader(const QString &FileLocation, QObject *parent = nullptr);

    /**
     * @brief Destructor for the fileReader object.
     */
    ~fileReader();

    /**
     * @brief Gets the speed data from the file.
     *
     * @return The speed data as a QString.
     */
    Q_INVOKABLE QString getDataSpeed();

    /**
     * @brief Gets the fuel state data from the file.
     *
     * @return The fuel state data as a boolean.
     */
    Q_INVOKABLE bool getDataFuelState();

    /**
     * @brief Reads all data from the file and updates the internal state.
     */
    Q_INVOKABLE void readAllData();

signals:
    /**
     * @brief Signal emitted when data is changed.
     */
    void DataChanged();

private:
    QString DataSpeed;  ///< The speed data.
    bool DataFuelState; ///< The fuel state data.
    QFile file_object;  ///< The file object used for reading.

public slots:

};

#endif // FILE_READER_H
