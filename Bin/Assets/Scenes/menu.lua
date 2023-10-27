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
        posy = "0.19",
        sizex = "0.225",
        sizey = "0.6",
        img = "m_carInfoPanel"
    }
}
selectVehicleButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.78",
        posy = "0.8",
        sizex = "0.19",
        sizey = "0.12",
        img = "m_selectVehicleButton"
    }
}

logoImg = {
    UIImageLM = { 
        interactive = "",
        posx = "0.01",
        posy = "0.87",
        sizex = "0.15",
        sizey = "0.13",
        img = "LogoImg"
    }
}

falconPreview = {
    Transform = {
        position = "0 -11 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "BlueFalcon_Out.mesh"
    },
    Rotator = {
        Speed = "-0.05"
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


entities = {"ButtonManager", "MenuBackgroundMesh", "falconPreview", "selectVehicleTitle", "carInfoPanel", "selectVehicleButton", "skyboxMesh", "backMesh", "mainCam", "logoImg", "menuBack", "audioHolder"}