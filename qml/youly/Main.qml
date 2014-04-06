import QtQuick 2.0
import QtQuick.Window 2.0
import Youly.Components 1.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0
import "components"

Item {
    id: main
    width: 320 //Screen.width
    height: 568 //Screen.height

    Camera {
        id: camera
    }

    VideoOutput {
        source: camera
        fillMode: VideoOutput.Stretch
    }

    NavView {
        /*onStateChange: {
            if (newState != "mid")
                Qt.createQmlObject('import QtQuick 2.0; import QtGraphicalEffects 1.0; FastBlur {anchors.fill:camera;source:camera;radius:100}', camera, "blur");
        }*/
    }


}
