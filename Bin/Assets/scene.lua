
coche = {
    Transform = {
        position = "0 6 0",
        rotation = "0 0 0",
        scale = "10 10 10"
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
        mass = 1
    }
}

track = {
    Transform = {
        position = "0 -30 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "AllTrack.mesh"
    },
    RigidBodyComponent = {
        mass = 0;
    }
}

mainCam = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        FOV = "60",
        target = "coche" ,
        main = ""
    },
    AudioListener = {}
}

entities = { "coche", "mainCam", "track"}