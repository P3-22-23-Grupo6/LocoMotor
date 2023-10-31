ButtonManager = {
    SceneChangeButton = {},
    AudioSource = {
        vol = "0.2",
        soundDimension = "2D"
    }
}
audioHolder = {
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/MenuMusic.mp3",
        loopStart = "17105",
        loopEnd = "214244",
        soundDimension = "2D",
        vol = "0.2"
    },
}
mainCam = {
    Transform = {
        position = "0 3 20",
        rotation = "15 -30 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        CameraMode = 0,
        FOV = "50",
        main = ""
    },
    CameraPanner = 
    { 
        speed = "0.4"
    }
}
startButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.5",
        posy = "0.7",
        sizex = "0.3",
        sizey = "0.15",
        img = "UIPanel"
    },
    UITextLM = {
        font =  "THEBOLDFONT",
        text = "Presiona un boton para comenzar",
        posx =  "0",
        posy = "0.7",
        align = "center",
        sizex = "0.03",
        sizey = "0.03",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1"
    }
}
menuMeshScene = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "MenuMeshScene.mesh"
    }
}
entities = {"ButtonManager", "audioHolder", "mainCam", "startButton", "menuMeshScene"}