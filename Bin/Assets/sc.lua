Button = {
    UIImageLM = { 
        interactive = "",
        posx = ".4",
        posy = ".5",
        sizex = ".2",
        sizey = ".1"
    },
    SceneChangeButton = {}
}

buttonText = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "BrunoAce",
        text = "RACE",
        posx =  "0",
        posy =  ".525",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1",
    }
}

carGraphic = {
    Transform = {
        position = "0 -15 -30",
        rotation = "0 180 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
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
        posx =  "0",
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

entities = {"Button", "titleText", 
    "mainCam", "buttonText", "carGraphic"}