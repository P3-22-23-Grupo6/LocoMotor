ButtonManager = {
    SceneChangeButton = {}
}

locomotorImg = {
    MeshRenderer = {
        file = "SkyboxMesh.mesh"
    }
}

raceButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0",
        posy = ".55",
        sizex = ".45",
        sizey = ".3",
        img = "UIPanel",
        top = "20"
    },
    UITextLM = {
        font =  "Heavitas",
        text = "RACE",
        posx =  "-.45",
        posy = ".625",
        align = "left",
        sizex = "0.45",
        sizey = "0.15",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1"
    }
}

menuBack = {
    UIImageLM = { 
        posx = ".75",
        posy = ".80",
        sizex = ".2",
        sizey = ".2",
        img = "LocomotorImg",
        top = "-1000"
    }
}

speedButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.0",
        posy = "0.4",
        sizex = "0.3",
        sizey = "0.15",
        img = "UIPanel"
    },
    UITextLM = {
        font =  "Heavitas",
        text = "100cc",
        posx =  "-.45",
        posy = "0.44",
        align = "left",
        sizex = "0.3",
        sizey = "0.075",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1"
    }
}

carGraphic = {
    Transform = {
        position = "0 -10 -30",
        rotation = "0 160 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    Rotator = {
        Speed = "0.05"
    }
}

titleText = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UIImageLM = { 
        posx = ".40",
        posy = "-0.01",
        sizex = "0.55",
        sizey = "0.55",
        img = "G6Logo"
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
        CameraMode = 0,
        FOV = "60",
        main = ""
    },
}

-- mainCam = {
--     Transform = {
--         position = "0 0 0",
--         rotation = "0 0 0",
--         scale = "1 1 1"
--     },
--     Camera = {
--         main = ""
--     }
-- }

entities = {"ButtonManager", "raceButton", "speedButton", "locomotorImg",
"titleText", "mainCam", "carGraphic"}