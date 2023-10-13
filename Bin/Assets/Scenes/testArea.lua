mainCam = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        CameraMode = 0,
        FOV = "60",
        target = "coche" ,
        main = "",
        initialOffset = ""
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "0 1 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    PlayerController = {},
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    }
}
test_Plane00 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "test_Plane00.mesh"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
    }
}
gizmo_Axis = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Gizmo_Axis.mesh"
    }
}
velocityText = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "BrunoAce",
        text = "0 km/h",
        posx =  "0.1",
        posy =  "0.75",
        align = "center",
        sizex = "0.02",
        sizey = "0.02",
        topcolor = "1 0 0",
        bottomcolor = "1 0 0",
    }
}
consoleDebug = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "BBB",
        text = "Debug Console",
        posx = "0",
        posy = "0.2",
        sizex = ".3",
        sizey = ".1",
        align = "center",
        topcolor = "0.95 0.95 0",
        bottomcolor = "0.12 0.91 0",
    }
}
entities = { "coche", "mainCam", "test_Plane00", "velocityText", "gizmo_Axis", "consoleDebug"}