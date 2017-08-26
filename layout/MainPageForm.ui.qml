import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    property alias button0: button0
    property alias button1: button1
    property alias button2: button2
    property alias button3: button3
    property alias textField: textField
    property alias textArea: textArea
    property alias progressBar: progressBar

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
            id: textArea
            text: qsTr("")
            enabled: false
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        TextField {
            id: textField
            text: qsTr("")
            enabled: false
            Layout.fillHeight: false
            Layout.fillWidth: true
        }

        ColumnLayout {
            id: columnLayout1
            width: 100
            height: 100
            spacing: 0
            Layout.fillWidth: true

            Button {
                id: button0
                text: qsTr("")
                enabled: false
                Layout.fillWidth: true
            }

            Button {
                id: button1
                text: qsTr("")
                enabled: false
                Layout.fillWidth: true
            }

            Button {
                id: button2
                text: qsTr("")
                enabled: false
                Layout.fillWidth: true
            }

            Button {
                id: button3
                text: qsTr("")
                enabled: false
                Layout.fillWidth: true
            }
        }

        ProgressBar {
            id: progressBar
            Layout.fillWidth: true
            value: 0
        }
    }
}
