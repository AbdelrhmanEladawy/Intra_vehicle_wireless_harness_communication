#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "radialbar.h"
#include "get_data/file_reader.h"
#include "get_data/jsonreader.h"

/**
 * @brief Main function for the application
 *
 * This function sets up the QGuiApplication, QQmlApplicationEngine, and registers
 * the custom QML type RadialBar. It then loads the QML file and initializes file
 * readers for text and JSON files, making them available in the QML context.
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return int Application exit status
 */
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Register the RadialBar type with QML
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");

    // Define the URL to the main QML file
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    // Connect the QML engine's objectCreated signal to handle QML loading errors
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    // Load the main QML file
    engine.load(url);

    // Define paths for the text and JSON files
    QString homePath = QDir::homePath();
    QString filePath = QDir(homePath).filePath("text.txt");
    QString jsonPath = QDir(homePath).filePath("jsonFileBBB.json");

    // Initialize file readers for text and JSON files
    fileReader text_file(filePath, &app);
    jsonReader json_file(jsonPath, &app);

    // Expose the file readers to the QML context
    engine.rootContext()->setContextProperty("FileReader", &text_file);
    engine.rootContext()->setContextProperty("jsonReader", &json_file);

    // Execute the application
    return app.exec();
}
