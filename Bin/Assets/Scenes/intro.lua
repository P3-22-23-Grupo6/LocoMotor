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
        position = "15 0 0",
        rotation = "20 30 0",
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
        speed = "0.1"
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
SkyboxMeshNew = {
    Transform = {
        position = "0 0 20",
        rotation = "0 0 0",
        scale = "2 2 2"
    },
    MeshRenderer = {
        file =  "SkyboxMeshNew.001.mesh",
        static = "true"
    }
}
OnePlayerButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.25",
        posy = "0.7",
        sizex = "0.26",
        sizey = "0.17",
        img = "m_OnePlayerButton00"
    }
}
TwoPlayerButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.52",
        posy = "0.7",
        sizex = "0.26",
        sizey = "0.17",
        img = "m_TwoPlayerButton00"
    }
}
selectText = {
    UIImageLM = { 
        interactive = "",
        posx = "0.4",
        posy = "0.66",
        sizex = "0.26",
        sizey = "0.065",
        img = "m_selectToStartText"
    }
}
entities = {"ButtonManager", "audioHolder", "mainCam", "menuMeshScene", "SkyboxMeshNew", "OnePlayerButton", "TwoPlayerButton", "selectText"}