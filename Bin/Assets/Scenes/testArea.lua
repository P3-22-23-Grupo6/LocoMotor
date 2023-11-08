mainCam = {
    Transform = {
        position = "-5 4 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        FOV = "55",
        target = "coche" ,
        main = "",
        initialOffset = "",
        CameraMode = 1
    },
    AudioListener = {}
}
secondCam = {
    Transform = {
        position = "5 4 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        FOV = "55",
        target = "cocheDos" ,
        main = "",
        initialOffset = "",
        CameraMode = 2
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "-5 4 10",
        rotation = "0 0 0",
        scale = "0.5 0.5 0.5"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav",
        volume = 0.2
    },
    PlayerController = {
        PlayerIndex = 0,
        PlayerSpeed = 170
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
cocheDos = {
    Transform = {
        position = "5 4 10",
        rotation = "0 0 0",
        scale = "0.5 0.5 0.5"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav",
        volume = 0.2
    },
    PlayerController = {
        PlayerIndex = 1,
        PlayerSpeed = 170
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
        posx =  "0.4",
        posy =  ".02",
        align = "center",
        sizex = "0.03",
        sizey = "0.03",
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
        checkpoint00 = "1.06, 1.75, -0.22",
        checkpoint01 = "1.89, 4.78, -142.14",
        checkpoint02 = "-0.97, 15.04, -275.17",
        checkpoint03 = "-47.67, 66.74, -454.49",
        checkpoint04 = "-168.6, 61.73, -452.73",
        checkpoint05 = "-205.08, 25.07, -385.2",
        checkpoint06 = "-210.47, 2.69, -272.89",
        checkpoint07 = "-212.05, 0.66, -144.38",
        checkpoint08 = "-215.97, 5.27, -20.68",
        checkpoint09 = "-260.99, 20.91, 126.23",
        checkpoint10 = "-356.1, 34.23, 143.37",
        checkpoint11 = "-411.52, 39.04, 49.6",
        checkpoint12 = "-319.5, 42.54, -39.2",
        checkpoint13 = "-182.49, 42.19, -24.66",
        checkpoint14 = "-19.93, 52.37, -20.0",
        checkpoint15 = "160.56, 38.26, -19.46",
        checkpoint16 = "300.99, 37.44, -33.43",
        checkpoint17 = "501.4, 30.73, -144.07",
        checkpoint18 = "645.6, 21.0, -161.63",
        checkpoint19 = "1033.46, 12.69, -104.24"
    }
}
Road00 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Road.00.mesh",
        static = "true"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
    }
}
Road01 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Road.01.mesh",
        static = "true"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
    }
}
Road02 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Road.02.mesh",
        static = "true"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
    }
}
Road03 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Road.03.mesh",
        static = "true"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
    }
}
Beach = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Beach.mesh",
        static = "true"
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = ""
    }
}
waterPlane = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "WaterPlane.mesh",
        static = "true"
    }
}
Terrain00 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Terrain.00.mesh",
        static = "true"
    }
}
Terrain01 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Terrain.01.mesh",
        static = "true"
    }
}
Terrain02 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Terrain.02.mesh",
        static = "true"
    }
}
Terrain03 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Terrain.03.mesh",
        static = "true"
    }
}
SkyboxMeshNew = {
    Transform = {
        position = "0 0 20",
        rotation = "0 0 0",
        scale = "3 3 3"
    },
    MeshRenderer = {
        file =  "SkyboxMesh.mesh",
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
        text = "1/3",
        posx =  "0.1",
        posy =  "0.75",
        align = "center",
        sizex = "0.02",
        sizey = "0.02",
        topcolor = "1 0 0",
        bottomcolor = "1 0 0",
    }
}
positionText = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "THEBOLDFONT",
        text = "1/3",
        posx =  "0",
        posy =  ".02",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "1 1 1",
        bottomcolor = "1 1 1",
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
--EnemyCar01 = {
--    Transform = {
--        position = "0 4 -10",
--        rotation = "0 0 0",
--        scale = "1 1 1"
--    },
--    MeshRenderer = {
--        file =  "Pelican.mesh"
--    },
--    AudioSource = {
--        loops= -1,
--        playonStart = "Assets/Sounds/engine.wav"
--    },
--    EnemyAI = {
--        enemySpeed = "0.5",
--        StartSeparation = "1"
--    },
--    RigidBodyComponent = {
--        mass = 1,
--        friction = "0.0"
--    }
--}
do ---------------------   UI   ------------------------------
    timerText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "00:00:000",
            posx =  ".1",
            posy =  ".15",
            align = "left",
            sizex = "0.08",
            sizey = "0.08",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    laptimerText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "00:00:000",
            posx =  ".1",
            posy =  ".05",
            align = "left",
            sizex = "0.08",
            sizey = "0.08",
            topcolor = "0.49 .88 .89",
            bottomcolor = "0.49 .88 .89",
        }
    }
    lapsText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "0 / 3",
            posx =  "-0.45",
            posy =  ".9",
            align = "left",
            sizex = "0.1",
            sizey = "0.1",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    positionText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "3 rd",
            posx =  "0.45",
            posy =  ".9",
            align = "right",
            sizex = "0.1",
            sizey = "0.1",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    --countdownText = {
    --    Transform = {
    --        position = "0 0 0",
    --        rotation = "0 0 0",
    --        scale = "1 1 1"
    --    },
    --    UITextLM = {
    --        font =  "Heavitas",
    --        text = "GO!",
    --        posx =  "0",
    --        posy =  ".3",
    --        align = "center",
    --        sizex = "0.15",
    --        sizey = "0.15",
    --        topcolor = "1 1 1",
    --        bottomcolor = "1 1 1",
    --    }
    --}
    velocityText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "100 km/h",
            posx =  "-0.45",
            posy =  ".05",
            align = "left",
            sizex = "0.05",
            sizey = "0.05",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
end ----------------------------------------------------------
turbo00 = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Turbo.00.mesh",
        static = "",
        invisible = ""
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = "",
        isTrigger = ""
    },
    Boost = {
        thrust = 8000,
    },
    AudioSource = {
        vol = "1"
    }
}
wall00 = {
    Transform = {
        position = "0 -6 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Wall.00.mesh",
        static = "",
        invisible = ""
    },
    RigidBodyComponent = {
        mass = 0,
        friction = "0.0"
    }
}
wall01 = {
    Transform = {
        position = "0 -6 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Wall.01.mesh",
        static = "",
        invisible = ""
    },
    RigidBodyComponent = {
        mass = 0,
        friction = "0.0"
    }
}
entities = { "coche", "cocheDos", "mainCam", "secondCam", "velocityText", "consoleDebug", "Test_Track_00", "portrait01Img", "portrait02Img", "counter01Text",
"Road00", "Road01", "Road02", "Road03", "Beach", 
"Terrain00", "Terrain01", "Terrain02", "Terrain03", "waterPlane",
"turbo00", "wall00", "wall01",
"counter02Text", "SkyboxMeshNew", "raceManager", "tube", "EnemyCar02", "EnemyCar01", "EnemyCar02", "EnemyCar03", "Roads", "positionText", "Extras",
"lapsText", "positionText", "countdownText", "velocityText", "timerText", "laptimerText",}