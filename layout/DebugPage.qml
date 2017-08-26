import QtQuick 2.8

DebugPageForm {
    Connections {
        target: compatibility
        onAppendDebugText: debugArea.append(text)
        onUpdateDebugBar: debugBar.value = value

    }

    function get(url, level, time) {
        var xmlhttp = new XMLHttpRequest()
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState === XMLHttpRequest.DONE && xmlhttp.status == 200)
                parse(xmlhttp.responseText, level, ++time)
        }
        xmlhttp.open("GET", url, true)
        xmlhttp.send()
    }

    function search(str, level) {
        germanButton.enabled = false
        frenchButton.enabled = false
        japaneseButton.enabled = false
        russianButton.enabled = false
        spanishButton.enabled = false
        get("https://cichang.hjapi.com/v2/book/search_by_tag?Query="
            + str + ",%E7%BD%91%E6%A0%A1", level, 0)
    }

    function parse(response, level, time) {
        var index = 0, array = JSON.parse(response)
        if (time === 1) {
            for (index = 0; index < array.data.items.length; ++index)
                if (array.data.items[index].name.includes(level)) break
            if (index !== array.data.items.length)
                get("https://cichang.hjapi.com/v2/book/" + array.data.items[index].id, time)
        } else {
            compatibility.setUnitID(array.data.unitCount)
            compatibility.load(array.data.sentAudioResource.version,
                               array.data.textResource.version, array.data.id)
        }
    }

    germanButton.onClicked: search("%E5%BE%B7%E8%AF%AD", "B2")
    frenchButton.onClicked: search("%E6%B3%95%E8%AF%AD", "B2")
    japaneseButton.onClicked: search("%E6%97%A5%E8%AF%AD", "N1")
    russianButton.onClicked: search("%E4%BF%84%E8%AF%AD", "B1")
    spanishButton.onClicked: search("%E8%A5%BF%E7%8F%AD%E7%89%99%E8%AF%AD", "B2")
}
