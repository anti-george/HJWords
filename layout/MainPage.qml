import QtQuick 2.7

MainPageForm {
    Connections {
        target: compatibility
        onAppendText: textArea.append(text)
        onUpdateText: {
            textField.clear()
            button0.text = list[0]
            button0.enabled = button0.text.length
            button1.text = list[1]
            button1.enabled = button1.text.length
            button2.text = list[2]
            button2.enabled = button2.text.length
            button3.text = list[3]
            button3.enabled = button3.text.length
            textArea.text = list[4]
        }
        onEnableTextField: textField.enabled = true
        onDisableTextField: textField.enabled = false
        onUpdateProgressBar: progressBar.value = value
    }

    button0.onClicked: {
        if (textField.enabled) compatibility.sendBackText(textField.text)
        else compatibility.sendBackText(button0.text)
    }

    button1.onClicked: {
        if (!textField.enabled) compatibility.sendBackText(button1.text)
        else if (isNaN(textField.text)) textField.clear()
        else {
            var num = parseInt(textField.text)
            if (num !== parseFloat(textField.text)) textField.clear()
            else if (num < 1 || num > compatibility.getUnitID()) textField.clear()
            else
            {
                compatibility.sendBackText(textField.text)
                textField.enabled = false
            }
        }
    }

    button2.onClicked: {
        if (button3.enabled) compatibility.sendBackText(button2.text)
        else compatibility.splashScreen()
    }

    button3.onClicked: compatibility.sendBackText(button3.text)
}
