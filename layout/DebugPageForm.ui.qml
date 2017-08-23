import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    property alias debugBar: debugBar
    property alias debugArea: debugArea

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

        ProgressBar {
            id: debugBar
            Layout.fillWidth: true
            value: 0
        }
    }
}
