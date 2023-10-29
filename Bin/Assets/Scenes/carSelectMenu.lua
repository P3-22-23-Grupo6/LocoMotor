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
selectVehicleTitle = {
    UIImageLM = { 
        posx = "0",
        posy = "0",
        sizex = "0.24",
        sizey = "0.06",
        img = "m_selectVehicleTitle"
    }
}
carInfoPanel = {
    UIImageLM = { 
        posx = "0.02",
        posy = "0.1",
        sizex = "0.25",
        sizey = "0.7",
        img = "m_carInfoPanelFalcon"
    }
}
selectPlayerOne = {
    UIImageLM = { 
        interactive = "",
        posx = "0.71",
        posy = "0.62",
        sizex = "0.3",
        sizey = "0.22",
        img = "m_PlayerOneSelect00"
    }
}
selectPlayerTwo = {
    UIImageLM = { 
        interactive = "",
        posx = "0.65",
        posy = "0.77",
        sizex = "0.3",
        sizey = "0.22",
        img = "m_PlayerTwoSelect00"
    }
}
goToIntroButton = {
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
Vehicle_Portrait = {
    UIImageLM = { 
        posx = "0.3",
        posy = "-0.05",
        sizex = "0.55",
        sizey = "1",
        img = "Portrait_Falcon",
        top = "-10000"
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
arrowRightButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.8",
        posy = "0.4",
        sizex = "0.08",
        sizey = "0.13",
        img = "ArrowRight00"
    }
}
arrowLeftButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.3",
        posy = "0.4",
        sizex = "0.08",
        sizey = "0.13",
        img = "ArrowLeft00"
    }
}
--skyboxMesh = {
--    MeshRenderer = {
--        file = "SkyboxMeshNew.001.mesh"
--    },Transform = {
--        position = "0 0 0",
--        rotation = "0 180 0",
--        scale = "1 1 1"
--    }
--}
--backMesh = {
--    Transform = {
--        position = "0 -5 -10",
--        rotation = "0 180 0",
--        scale = "1 1 1"
--    },
--    MeshRenderer = {
--        file =  "MENU.mesh"
--    }
--}


entities = {"ButtonManager", "MenuDecalMesh", "goToIntroButton", "MenuBackgroundMesh", "falconPreview", "selectVehicleTitle", "carInfoPanel", "selectPlayerTwo", "selectPlayerOne",
"skyboxMesh", "backMesh", "mainCam", "logoImg", "menuBack", "audioHolder", "Vehicle_Portrait", "arrowRightButton", "arrowLeftButton"}