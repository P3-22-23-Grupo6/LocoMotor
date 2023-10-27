mainCam = {
    Transform = {
        position = "-5 4 0",
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
        position = "-5 4 0",
        rotation = "0 0 0",
        scale = "1 1 1"
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
        name = "exhaustDos",
        file = "Racers/JetEngine2"
    }
}
secondCam = {
    Transform = {
        position = "5 4 0",
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
        position = "5 4 0",
        rotation = "0 0 0",
        scale = "1 1 1"
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
        checkpoint0 = "0 2 -10",
        checkpoint1 = "0 2 -40",
        checkpoint2 = "0 4 -80",
        checkpoint3 = "0 6 -120",
        checkpoint4 = "0 8 -160",
        checkpoint5 = "0 10 -200",
        checkpoint6 = "0 12 -240",
        checkpoint7 = "0 12 -280",
        checkpoint8 = "0 12 -320",
        checkpoint9 = "0 2 -10"
    }
}
test_Plane00 = {
    Transform = {
        position = "0 0 0",
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
Roads = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Roads.mesh",
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
portrait01Img = {
    UIImageLM = { 
        posx = "0",
        posy = "0.1",
        sizex = "0.1",
        sizey = "0.1",
        img = "Portrait_01",
        top = "20"
    }
}
portrait02Img = {
    UIImageLM = { 
        posx = "0",
        posy = "0.4",
        sizex = "0.1",
        sizey = "0.1",
        img = "Portrait_02",
        top = "10"
    }
}
EnemyCar01 = {
    Transform = {
        position = "0 4 -10",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Stinger.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "20",
        StartSeparation = "0"
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    }
}
entities = { "coche", "cocheDos", "mainCam", "secondCam", "test_Plane00", "velocityText", "consoleDebug", "Test_Track_00", "portrait01Img", "portrait02Img", "counter01Text",
"counter02Text", "SkyboxMeshNew", "raceManager", "tube", "EnemyCar02", "EnemyCar01", "Roads"}