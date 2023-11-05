mainCam = {
    Transform = {
        position = "-144 10 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        FOV = "60",
        target = "coche" ,
        main = "",
        initialOffset = "",
        CameraMode = 0
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "-144 10 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav",
        volume = 0.2
    },
    PlayerController = {
        PlayerIndex = 0,
        PlayerSpeed = 200
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
raceManager = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "THEBOLDFONT",
        text = "0 fps",
        posx =  "0",
        posy =  ".02",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1",
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
        checkpoint1 = "-144.2309, 10.6283, 10.6283",
        checkpoint2 = "-54.8094, 10.6283, -136.9770",
        checkpoint3 = "59.2961, 10.6283, -136.9770",
        checkpoint4 = "140.0414, 10.6283, 0.0000",
        checkpoint5 = "59.2961, 10.628, 133.8742",
        checkpoint6 = "-54.8094, 10.6283, 133.8742",
        checkpoint7 = "-144.2309, 10.6283, 10.6283"
    }
}
circleTrack = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "CircleTrack.mesh",
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
        position = "-144 20 0",
        rotation = "0 180 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file = "Pelican.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "2",
        StartSeparation = "1"
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0",
        isTrigger = ""
    }
}

entities = { "coche", "cocheDos", "mainCam", "secondCam", "circleTrack", "velocityText", "consoleDebug", "Test_Track_00", "portrait01Img", "portrait02Img", "counter01Text",
"counter02Text", "SkyboxMeshNew", "raceManager", "tube", "EnemyCar02", "EnemyCar01", "EnemyCar02", "EnemyCar03", "Roads", "test_Plane01"}