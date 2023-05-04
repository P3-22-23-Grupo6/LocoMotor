ButtonManager = {
    SceneChangeButton = {}
}

raceButton = {
    UIImageLM = { 
        interactive = "",
        posx = ".15",
        posy = ".7",
        sizex = ".2",
        sizey = ".1",
        img = "UIPanel"
    },

    UITextLM = {
        font =  "Heavitas",
        text = "RACE",
        posx =  "-.25",
        posy =  ".725",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1"
    }
}

locomotorImg = {
    UIImageLM = { 
        interactive = "",
        posx = ".75",
        posy = ".85",
        sizex = ".2",
        sizey = ".1",
        img = "LocomotorImg"
    },

    UITextLM = {
        font =  "Heavitas",
        text = "RACE",
        posx =  "-.25",
        posy =  ".725",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1"
    }
}

speedButton = {
    UIImageLM = { 
        interactive = "",
        posx = ".15",
        posy = ".5",
        sizex = ".2",
        sizey = ".1",
        img = "UIPanel"
    },

    UITextLM = {
        font =  "Heavitas",
        text = "100cc",
        posx =  "-.25",
        posy =  ".525",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
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
    UITextLM = {
        font =  "BrunoAce",
        text = "G6",
        posx =  ".25",
        posy =  ".2",
        align = "center",
        sizex = "0.3",
        sizey = "0.3",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1",
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