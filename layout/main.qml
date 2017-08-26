import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    title: qsTr("HJWords")

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Dictionary")
        }
        TabButton {
            text: qsTr("HJWords")
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        DebugPage {
        }
        MainPage {
        }
    }
}
