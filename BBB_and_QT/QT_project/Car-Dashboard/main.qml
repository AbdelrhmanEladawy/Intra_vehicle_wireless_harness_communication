import QtQuick 2.15
import CustomControls 1.0
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ApplicationWindow {
    width: 800
    height: 480
    visible: true
    title: qsTr("Car DashBoard")
    color: "#1E1E1E"
    // visibility: "FullScreen"

    // Function to get current time in HH:MM:SS format
    function getCurrentTime() {
        var currentDate = new Date();
        var hours = currentDate.getHours().toString().padStart(2, '0');
        var minutes = currentDate.getMinutes().toString().padStart(2, '0');
        var seconds = currentDate.getSeconds().toString().padStart(2, '0');
        return hours + ':' + minutes + ':' + seconds;
    }

    // Function to get current date in MM/DD/YYYY format
    function getCurrentData() {
        var currentDate = new Date();
        var dateString = currentDate.toLocaleDateString("en-US");
        return dateString;
    }

    // Timer to update time, date, and arrow states every 500 milliseconds
    Timer{
        id: time_date_update_timer
        repeat: true
        interval: 500
        running: true

        onTriggered: {
            current_time.text = getCurrentTime();
            current_data.text = getCurrentData();

            jsonReader.switchIntervalIndicator();
            if(jsonReader.getRightArrowState())
            { right_arrow.source = (jsonReader.getIntervalIndicator())? "qrc:/assets/right-arrow_gray.png" : "qrc:/assets/right-arrow_green.png"; }
            else
            { right_arrow.source = "qrc:/assets/right-arrow_gray.png" }

            if(jsonReader.getLeftArrowState())
            { left_arrow.source = (jsonReader.getIntervalIndicator())? "qrc:/assets/left-arrow_gray.png" : "qrc:/assets/left-arrow_green.png"; }
            else
            { left_arrow.source = "qrc:/assets/left-arrow_gray.png" }
        }
    }

    // Timer to read data from JSON file every 100 milliseconds
    Timer{
        id: get_data_timer
        repeat: true
        interval: 100
        running: true

        onTriggered: {
            jsonReader.readAllData();
            speedLabel.text = jsonReader.getDataSpeed();
            radialBar.value = jsonReader.getDataTemperature();
            fuel_states.source = (jsonReader.getDataFuelState()) ? "qrc:/assets/fuelOn.png" : "qrc:/assets/fuelOff.png";
        }
    }

    // Shortcut to quit the application
    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }

    Image {
        id: dashboard
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        source: "qrc:/assets/Dashboard.svg"

        /* Top Bar Of Screen */
        Image {
            id: topBar
            width: parent.width/1.5
            height: parent.height/8.5
            source: "qrc:/assets/Vector 70.svg"

            anchors{
                top: parent.top
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }

            Image {
                id: weather_icon
                width: 30
                height: 25
                anchors{
                    top: parent.top
                    topMargin: 5
                    leftMargin: 65
                    left: parent.left
                }
                source: "qrc:/assets/weather.png"
            }

            /* Current Time */
            Label{
                id: current_time
                text: getCurrentTime()
                font.pixelSize: 20
                font.family: "Open Sans"
                font.bold: Font.DemiBold
                color: "#FFFFFF"
                anchors.top: parent.top
                anchors.topMargin: 3
                anchors.centerIn: parent.Center
                anchors.rightMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
            }

            /* Current Data */
            Label{
                id: current_data
                text: getCurrentData()
                font.pixelSize: 20
                font.family: "Inter"
                font.bold: Font.DemiBold
                color: "#FFFFFF"
                anchors.right: parent.right
                anchors.rightMargin: 60
                anchors.top: parent.top
                anchors.topMargin: 3
            }
        }

        /* Speed Label */
        Label{
            id:speedLabel
            text: "00"
            font.pixelSize: 80
            font.family: "Inter"
            color: "#01E6DE"
            font.bold: Font.DemiBold
            anchors.top: parent.top
            anchors.topMargin:Math.floor(parent.height * 0.35)
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label{
            id:km_h
            text: "KM/H"
            font.pixelSize: 20
            font.family: "Inter"
            color: "#01E6DE"
            font.bold: Font.Normal
            anchors.top:speedLabel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

        /* left and right arrow */
        Image {
            id: left_arrow
            anchors{
                top : topBar.bottom
                left: topBar.left
                // topMargin: 50
                // leftMargin: 85
            }
            width: 50
            height: 50
            source: "qrc:/assets/left-arrow_gray.png"
        }

        Image {
            id: right_arrow
            anchors{
                top : topBar.bottom
                right: topBar.right
                // topMargin: 25
                // rightMargin: 85
            }
            width: 50
            height: 50
            source: "qrc:/assets/right-arrow_gray.png"
        }

        /* Right Road */
        Image {
            id: rightRoad
            width: 127
            height: 397
            anchors{
                right: km_h.right
                rightMargin: 55
                bottom: parent.bottom
                bottomMargin: 26.50
            }
            source: "qrc:/assets/Vector 1.svg"
        }

        /* Left Road */
        Image {
            id: leftRoad
            width: 127
            height: 397
            anchors{
                left: km_h.left
                leftMargin: 55
                bottom: parent.bottom
                bottomMargin: 26.50
            }
            source: "qrc:/assets/Vector 2.svg"
        }

        /* Right Side gear */
        RowLayout{
            spacing: 20
            anchors{
                right: parent.right
                rightMargin: 55
                bottom: parent.bottom
                bottomMargin: 26.50 + 25
            }
            Label{
                text: "P"
                font.pixelSize: 20
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                color: "#FFFFFF"
            }
            Label{
                text: "R"
                font.pixelSize: 20
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                opacity: 0.2
                color: "#FFFFFF"
            }
            Label{
                text: "N"
                font.pixelSize: 20
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                opacity: 0.2
                color: "#FFFFFF"
            }
            Label{
                text: "D"
                font.pixelSize: 20
                font.family: "Inter"
                font.bold: Font.Normal
                font.capitalization: Font.AllUppercase
                opacity: 0.2
                color: "#FFFFFF"
            }
        }

        /*Left Side Icons*/
       Image {
           id:first_left_side_icon
           width: 60
           height: 50
           anchors{
               left: parent.left
               leftMargin: 50
               bottom: speedLabel.top
               bottomMargin: 12
           }
           source: "qrc:/assets/Parking lights.svg"
       }
       Image {
           id:second_left_side_icon
           width: 40
           height: 60
           anchors{
               left: parent.left
               leftMargin: 50
               top: first_left_side_icon.bottom
               topMargin: 12
           }
           source: "qrc:/assets/Lights.svg"
       }
       Image {
           id:thrid_left_side_icon
           width: 50
           height: 50
           anchors{
               left: parent.left
               leftMargin: 50
               top: second_left_side_icon.bottom
               topMargin: 12
           }
           source: "qrc:/assets/Low beam headlights.svg"
       }
       Image {
           id:fourth_left_side_icon
           width: 50
           height: 50
           anchors{
               left: parent.left
               leftMargin: 50
               top: thrid_left_side_icon.bottom
               topMargin: 12
           }
           source: "qrc:/assets/Rare fog lights.svg"
       }

       /*Right Side Icons*/
       Image {
           id:first_right_side_icon
           width: 56.83
           height: 36.17
           anchors{
               right: parent.right
               rightMargin: 50
               bottom: speedLabel.top
               bottomMargin: 12
           }
           opacity: 0.4
           source: "qrc:/assets/FourthRightIcon.svg"
       }
       Image {
           id:second_right_side_icon
           width: 56.83
           height: 36.17
           anchors{
               right: parent.right
               rightMargin: 50
               top: first_right_side_icon.bottom
               topMargin: 12
           }
           opacity: 0.4
           source: "qrc:/assets/thirdRightIcon.svg"
       }
       Image {
           id:thrid_right_side_icon
           width: 56.83
           height: 36.17
           anchors{
               right: parent.right
               rightMargin: 50
               top: second_right_side_icon.bottom
               topMargin: 12
           }
           opacity: 0.4
           source: "qrc:/assets/SecondRightIcon.svg"
       }
       Image {
           id:fourth_right_side_icon
           width: 36
           height: 45
           anchors{
               right: parent.right
               rightMargin: 50
               top: thrid_right_side_icon.bottom
               topMargin: 12
           }
           source: "qrc:/assets/FirstRightIcon.svg"
       }

       // Progress Bar
       RadialBar {
           id:radialBar
           anchors{
               verticalCenter: parent.verticalCenter
               left: parent.left
               leftMargin: parent.width / 6
               bottomMargin: 50
           }

           width: 100
           height: 100
           penStyle: Qt.RoundCap
           dialType: RadialBar.NoDial
           progressColor: "#01E4E0"
           backgroundColor: "transparent"
           dialWidth: 8
           startAngle: 90
           value:25
           spanAngle: 3.6 * value
           minValue: 0
           maxValue: 120
           textFont {
               family: "inter"
               italic: false
               bold: Font.Medium
               pixelSize: 25
           }
           showText: false
           suffixText: ""
           textColor: "#FFFFFF"

           ColumnLayout{
               anchors.centerIn: parent
               Label{
                   text: radialBar.value + '°'
                   font.pixelSize: 25
                   font.family: "Inter"
                   font.bold: Font.Normal
                   color: "#FFFFFF"
                   Layout.alignment: Qt.AlignHCenter
               }

               Label{
                   id: temperature_text
                   text: "temperature"
                   font.pixelSize: 20
                   font.family: "Inter"
                   font.bold: Font.Normal
                   opacity: 0.8
                   color: "#FFFFFF"
                   Layout.alignment: Qt.AlignHCenter
               }
           }
       }

       ColumnLayout{
           spacing: 10

           anchors{
               verticalCenter: parent.verticalCenter
               right: parent.right
               rightMargin: parent.width / 6
           }

           RowLayout{
               spacing: 20
               Image {
                   width: 20
                   height: 10
                   source: "qrc:/assets/Group 28.svg"
               }

               ColumnLayout{
                   Label{
                       text: "188 KM"
                       font.pixelSize: 15
                       font.family: "Inter"
                       font.bold: Font.Normal
                       opacity: 0.8
                       color: "#FFFFFF"
                   }
                   Label{
                       text: "Distance"
                       font.pixelSize: 10
                       font.family: "Inter"
                       font.bold: Font.Normal
                       opacity: 0.8
                       color: "#FFFFFF"
                   }
               }
           }
           RowLayout{
               spacing: 30
               Image {
                   id : fuel_states
                   width: 60
                   height: 60
                   source: "qrc:/assets/fuelOn.png"
               }

               ColumnLayout{
                   Label{
                       text: "34 mpg"
                       font.pixelSize: 15
                       font.family: "Inter"
                       font.bold: Font.Normal
                       opacity: 0.8
                       color: "#FFFFFF"
                   }
                   Label{
                       text: "Avg. Fuel Usage"
                       font.pixelSize: 10
                       font.family: "Inter"
                       font.bold: Font.Normal
                       opacity: 0.8
                       color: "#FFFFFF"
                   }
               }
           }
           RowLayout{
               spacing: 30
               Image {
                   width: 20
                   height: 20
                   source: "qrc:/assets/speedometer.svg"
               }

               ColumnLayout{
                   Label{
                       text: "250000"
                       font.pixelSize: 15
                       font.family: "Inter"
                       font.bold: Font.Normal
                       opacity: 0.8
                       color: "#FFFFFF"
                   }
                   Label{
                       text: "Avg. Km"
                       font.pixelSize: 10
                       font.family: "Inter"
                       font.bold: Font.Normal
                       opacity: 0.8
                       color: "#FFFFFF"
                   }
               }
           }

       }

    }



}
