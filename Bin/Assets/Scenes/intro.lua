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
-- UI PANELS
backgroundImg = {
    UIImageLM = { 
        posx = "0",
        posy = "0",
        sizex = "1",
        sizey = "1",
        img = "MenuBackImage",
        top = "-10000"
    }
}
mainCam = {
    Transform = {
        position = "0 -10 6",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        CameraMode = 0,
        FOV = "34",
        main = ""
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
entities = {"ButtonManager", "backgroundImg", "audioHolder", "mainCam", "startButton"}