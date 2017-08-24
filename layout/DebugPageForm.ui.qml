import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    property alias debugBar: debugBar
    property alias debugArea: debugArea
    property alias germanButton: germanButton
    property alias frenchButton: frenchButton
    property alias japaneseButton: japaneseButton
    property alias russianButton: russianButton
    property alias spanishButton: spanishButton

    width: 360
    height: 640

    ColumnLayout {
        id: columnLayout
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
        anchors.topMargin: 6
        anchors.fill: parent

        TextArea {
            id: debugArea
            enabled: false
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100

            Button {
                id: frenchButton
                text: qsTr("FR")
                Layout.fillWidth: true
            }

            Button {
                id: germanButton
                text: qsTr("DE")
                Layout.fillWidth: true
            }

            Button {
                id: japaneseButton
                text: qsTr("JP")
                Layout.fillWidth: true
            }

            Button {
                id: russianButton
                text: qsTr("RU")
                Layout.fillWidth: true
            }

            Button {
                id: spanishButton
                text: qsTr("ES")
                Layout.fillWidth: true
            }
        }

        ProgressBar {
            id: debugBar
            Layout.fillWidth: true
            value: 0
        }
    }
}
