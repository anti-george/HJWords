import QtQuick 2.4

DebugPageForm {
    Connections {
        target: compatibility
        onAppendDebugText: debugArea.append(text)
        onUpdateDebugBar: debugBar.value = value
    }
}
