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
selectTrackTitle = {
    UIImageLM = { 
        posx = "0",
        posy = "0",
        sizex = "0.24",
        sizey = "0.06",
        img = "m_selectTrakTitle"
    }
}
selectTrackButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.71",
        posy = "0.76",
        sizex = "0.3",
        sizey = "0.22",
        img = "m_select"
    }
}

goToCarButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.02",
        posy = "0.8",
        sizex = "0.22",
        sizey = "0.16",
        img = "m_BackButton"
    }
}
logoImg = {
    UIImageLM = { 
        interactive = "",
        posx = "0.81",
        posy = "0.01",
        sizex = "0.2",
        sizey = "0.18",
        img = "LogoImg"
    }
}

MenuBackgroundMesh = {
    Transform = {
        position = "0 0 -10",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "MenuBackgroundMesh.mesh"
    }
}

mainCam = {
    Transform = {
        position = "0 0 6",
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
trackArrowRightButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.55",
        posy = "0.4",
        sizex = "0.08",
        sizey = "0.13",
        img = "ArrowRight00"
    }
}
trackArrowLeftButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0",
        posy = "0.4",
        sizex = "0.08",
        sizey = "0.13",
        img = "ArrowLeft00"
    }
}
trackMesh00 = {
    Transform = {
        position = "2 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "BlueFalcon_Out.mesh",
        static = "true"
    },
    Rotator = {
        Speed = "0.05"
    }
}
trackMesh01 = {
    Transform = {
        position = "2 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "PreviewTrack00.mesh",
        static = "true",
        invisible = "true"
    },
    Rotator = {
        Speed = "0.05"
    }
}
Portrait_TrackOne = {
    UIImageLM = { 
        posx = "0.06",
        posy = "0.14",
        sizex = "0.5",
        sizey = "0.6",
        img = "Portrait_TrackOne"
    }
}
entities = {"ButtonManager", "MenuDecalMesh", "goToIntroButton", "MenuBackgroundMesh", "falconPreview", "selectTrackTitle", "selectTrackButton",
"mainCam", "logoImg", "menuBack", "audioHolder", "trackArrowLeftButton", "trackArrowRightButton", "trackMesh00", "trackMesh01", "Portrait_TrackOne"}