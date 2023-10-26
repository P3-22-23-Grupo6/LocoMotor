mainCam = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        FOV = "60",
        target = "coche" ,
        main = "",
        initialOffset = "",
        CameraMode = 1
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "-30 40 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav",
        volume = 0.2
    },
    PlayerController = {
        PlayerIndex = 0
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0",
    },
    ParticleSystem = {
        name = "exhaust",
        file = "Racers/JetEngine2"
    }
}
secondCam = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        FOV = "60",
        target = "cocheDos" ,
        main = "",
        initialOffset = "",
        CameraMode = 2
    },
    AudioListener = {}
}
cocheDos = {
    Transform = {
        position = "-30 40 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav",
        volume = 0.2
    },
    PlayerController = {
        PlayerIndex = 1
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0",
    },
    ParticleSystem = {
        name = "exhaust",
        file = "Racers/JetEngine2"
    }
}
raceManager = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "BrunoAce",
        text = "0 fps",
        posx =  "0",
        posy =  ".02",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "0 0 0",
        bottomcolor = "0 0 0",
    },
    AudioSource = {
        loops= -1,
        loopStart = "17105",
        loopEnd = "214244",
        playonStart = "Assets/Sounds/mainTheme.mp3",
        soundDimension = "2D",
        vol = "1"
    },
    RaceManager = {
        checkpoint80 = "2 1 -5",
        checkpoint0 = "2 1 -10",
        checkpoint1 = "2 1 -27",
        checkpoint2 = "2 1 -44",
        checkpoint3 = "1 6 -62",
        checkpoint4 = "-10 15 -75",
        checkpoint5 = "-30 14 -71",
        checkpoint6 = "-42 6 -55",
        checkpoint7 = "-41 4 -53",
        checkpoint8 =  "-42 1 -43",
        checkpoint12 =  "-42 0 -24",
        checkpoint13 =  "-42 -0 -12",
        checkpoint14 =  "-42 -0 0",
        checkpoint15 =  "-42 -0 11",
        checkpoint16 =  "-42 -0 23",
        checkpoint17 =  "-42 1 36",
        checkpoint18 =  "-43 4 47",
        checkpoint19 =  "-50 6 55",
        checkpoint20 =  "-60 8 57",
        checkpoint21 =  "-69 8 53",
        checkpoint22 =  "-76 10 45",
        checkpoint23 =  "-77 10 34",
        checkpoint24 =  "-72 11 25",
        checkpoint25 =  "-63 12 20",
        checkpoint26 =  "-52 12 18",
        checkpoint27 =  "-41 12 17",
        checkpoint28 =  "-30 12 17",
        checkpoint29 =  "-18 12 17",
        checkpoint30 =  "-3 12 17",
        checkpoint31 =  "-7 13 17",
        checkpoint32 =  "21 10 17",
        checkpoint33 =  "46 10 15",
        checkpoint34 =  "60 11 -6",
        checkpoint35 =  "66 10 -1",
        checkpoint36 =  "77 9 -9",
        checkpoint37 =  "90 8 -11",
        checkpoint38 =  "105 7 -12",
        checkpoint39 =  "127 7 -12",
        checkpoint40 =  "147 4 -12",
        checkpoint41 =  "161 0 -12",
        checkpoint42 =  "180 0 -12",
        checkpoint43 =  "200 0 -12",
        checkpoint44 =  "224 1 -12",
        checkpoint45 =  "236 7 -12",
        checkpoint46 =  "255 13 -12",
        checkpoint47 =  "269 16 -12",
        checkpoint48 =  "286 18 -12",
        checkpoint49 =  "300 15 -12",
        checkpoint50 =  "313 9 -9",
        checkpoint51 =  "323 1 -3",
        checkpoint52 =  "329 -5 2",
        checkpoint53 =  "333 -10 9",
        checkpoint54 =  "338 -16 20",
        checkpoint55 =  "340 -20 30",
        checkpoint56 =  "341 -23 41",
        checkpoint57 =  "341 -24 50",
        checkpoint58 =  "341 -25 61",
        checkpoint59 =  "341 -23 71",
        checkpoint60 =  "341 -20 85",
        checkpoint61 =  "338 -15 97",
        checkpoint62 =  "320 -11 106",
        checkpoint63 =  "328 -7 118",
        checkpoint64 =  "319 -2 128",
        checkpoint65 =  "250 -5 145",
        checkpoint66 =  "228 7 160",
        checkpoint67 =  "222 8 178",
        checkpoint68 =  "227 8 192",
        checkpoint69 =  "237 9 200",
        checkpoint70 =  "250 10 203",
        checkpoint71 =  "278 17 186",
        checkpoint72 =  "285 18 167",
        checkpoint73 =  "289 18 139",
        checkpoint74 =  "285 17 107",
        checkpoint75 =  "273 19 89",
        checkpoint76 =  "254 17 77",
        checkpoint77 =  "232 14 75",
        checkpoint78 =  "209 10 75",
        checkpoint79 =  "183 7 76",
        checkpoint80 =  "187 5 76",
        checkpoint81 =  "129 5 72",
        checkpoint82 =  "99 8 60",
        checkpoint83 =  "58 10 51",
        checkpoint84 =  "45 12 51",
        checkpoint85 =  "29 1 51",
        checkpoint86 =  "7 1 45",
        checkpoint87 =  "2 1 27"
    }
}
test_Plane00 = {
    Transform = {
        position = "0 0 20",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "TestToWapo.mesh",
        static = "true"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
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
velocityText = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        type = "t",
        font = "BrunoAce",
        text = "0 km/h",
        posx =  "0.1",
        posy =  "0.75",
        align = "center",
        sizex = "0.02",
        sizey = "0.02",
        topcolor = "1 0 0",
        bottomcolor = "1 0 0",
    }
}
counter01Text = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        type = "t",
        font = "THEBOLDFONT",
        text = "1",
        posx =  "-.4325",
        posy =  "0.15",
        align = "left",
        sizex = "0.03",
        sizey = "0.03",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1",
    }
}
counter02Text = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        type = "t",
        font = "THEBOLDFONT",
        text = "2",
        posx =  "-.4325",
        posy =  "0.25",
        align = "left",
        sizex = "0.03",
        sizey = "0.03",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1",
    }
}
counter01Img = {
    UIImageLM = { 
        posx = "0",
        posy = "0.1",
        sizex = "0.1",
        sizey = "0.1",
        img = "Counter_01"
    }
}
portrait01Img = {
    UIImageLM = { 
        posx = "0",
        posy = "0.1",
        sizex = "0.1",
        sizey = "0.1",
        img = "Portrait_01"
    }
}
counter02Img = {
    UIImageLM = { 
        posx = "0",
        posy = "0.2",
        sizex = "0.1",
        sizey = "0.1",
        img = "Counter_01"
    }
}
portrait02Img = {
    UIImageLM = { 
        posx = "0",
        posy = "0.2",
        sizex = "0.1",
        sizey = "0.1",
        img = "Portrait_01"
    }
}
entities = { "coche", "cocheDos", "mainCam", "secondCam", "test_Plane00", "velocityText", "gizmo_Axis", "consoleDebug", "Test_Track_00", "counter01Img", "portrait01Img", "counter02Img", "portrait02Img", "counter01Text",
"counter02Text", "SkyboxMeshNew", "raceManager"}