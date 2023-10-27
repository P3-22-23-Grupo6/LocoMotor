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
        img = "m_carInfoPanel"
    }
}
selectVehicleButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.7",
        posy = "0.77",
        sizex = "0.3",
        sizey = "0.22",
        img = "m_selectVehicleButton"
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
Portrait_Falcon = {
    UIImageLM = { 
        interactive = "",
        posx = "0.42",
        posy = "0.12",
        sizex = "0.45",
        sizey = "0.75",
        img = "Portrait_Falcon"
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


entities = {"ButtonManager", "MenuDecalMesh", "goToIntroButton", "MenuBackgroundMesh", "falconPreview", "selectVehicleTitle", "carInfoPanel", "selectVehicleButton", 
"skyboxMesh", "backMesh", "mainCam", "logoImg", "menuBack", "audioHolder", "Portrait_Falcon"}