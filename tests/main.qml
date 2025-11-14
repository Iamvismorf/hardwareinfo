import QtQuick
import test

Window {
    visible: true
    color: "lightYellow"
    Timer {
        interval: 1
        repeat: true
        running: true
        onTriggered: {
            interval = 1000;
            Cpu.updateCpuUsage();
            console.log(Cpu.cpuUsage);
        }
    }
    Text {
        id: msg
        text: Cpu.cpuUsage
        color: "black"
        anchors.centerIn: parent
    }
    // Text {
    //     text: Cpu.num
    //     color: "black"
    //     anchors.top: msg.bottom
    //     anchors.left: msg.left
    //     anchors.topMargin: 16
    // }
}
