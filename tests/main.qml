import QtQuick
import QtQuick.Controls
import test

Window {
    visible: true
    color: "lightYellow"
    // Timer {
    //     interval: 1
    //     repeat: true
    //     running: true
    //     onTriggered: {
    //         interval = 1000;
    //         Cpu.updateCpuUsage();
    //         console.log(Cpu.cpuUsage);
    //     }
    // }
    Text {
        id: msg
        text: Ram.usedRam
        color: "black"
        anchors.centerIn: parent
    }
    Text {
        anchors.top: msg.bottom
        anchors.left: msg.left
        anchors.topMargin: 16
        text: `${(Ram.utilization * 100 | 0)}%`
    }

    // Text {
    //     text: Cpu.num
    //     color: "black"
    //     anchors.top: msg.bottom
    //     anchors.left: msg.left
    //     anchors.topMargin: 16
    // }
}
