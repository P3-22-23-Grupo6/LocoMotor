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
        CameraMode = 0
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "1 1.75 19",
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
        posx =  "0.46",
        posy =  ".01",
        align = "center",
        sizex = "0.02",
        sizey = "0.02",
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
        checkpoint19 = "1033.46, 12.69, -104.24",
        checkpoint20 = "1068.78, 9.54, 41.69",
        checkpoint21 = "1066.77, -34.08, 149.3",
        checkpoint22 = "1056.09, -127.8, 354.0",
        checkpoint23 = "1039.5, -103.58, 558.62",
        checkpoint24 = "1093.06, 7.06, 732.13",
        checkpoint25 = "1169.54, 170.6, 866.94",
        checkpoint26 = "1144.62, 262.14, 957.33",
        checkpoint27 = "1060.28, 297.99, 1023.01",
        checkpoint28 = "959.99, 285.54, 1065.52",
        checkpoint29 = "831.99, 222.15, 1092.19",
        checkpoint30 = "677.55, 115.63, 1094.89",
        checkpoint31 = "528.48, 31.74, 1014.16",
        checkpoint32 = "434.52, 0.67, 847.99",
        checkpoint33 = "393.49, -0.91, 765.05",
        checkpoint34 = "262.55, -0.15, 539.54",
        checkpoint35 = "142.1, 30.34, 414.19",
        checkpoint36 = "0.66, 18.65, 175.81",
        checkpoint37 = "2.18, 5.68, 110.03",
        checkpoint38 = "1.06, 1.75, -0.22",
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
UnderWater = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "UnderWater.mesh",
        static = "true"
    }
}
--positionText = {
--    Transform = {
--        position = "0 0 0",
--        rotation = "0 0 0",
--        scale = "1 1 1"
--    },
--    UITextLM = {
--        font =  "THEBOLDFONT",
--        text = "1/3",
--        posx =  "0",
--        posy =  ".02",
--        align = "center",
--        sizex = "0.05",
--        sizey = "0.05",
--        topcolor = "1 1 1",
--        bottomcolor = "1 1 1",
--    }
--}
--EnemyCar01 = {
--    Transform = {
--        position = "1 2 -10",
--        rotation = "0 0 0",
--        scale = "2 2 2"
--    },
--    MeshRenderer = {
--        file =  "Pelican.mesh"
--    },
--    AudioSource = {
--        loops= -1,
--        playonStart = "Assets/Sounds/engine.wav"
--    },
--    EnemyAI = {
--        enemySpeed = "0.4",
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
            font =  "THEBOLDFONT",
            text = "00:00:000",
            posx =  "-0.48",
            posy =  ".08",
            align = "left",
            sizex = "0.07",
            sizey = "0.07",
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
            font =  "THEBOLDFONT",
            text = "00:00:000",
            posx =  "-0.48",
            posy =  ".15",
            align = "left",
            sizex = "0.047",
            sizey = "0.047",
            topcolor = "1.0 0.68 0.2",
            bottomcolor = "1.0 0.68 0.2"
        }
    }
    lapsText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "THEBOLDFONT",
            text = "0/3 RONDAS",
            posx =  "-0.48",
            posy =  "0.015",
            align = "left",
            sizex = "0.036",
            sizey = "0.036",
            topcolor = "0.74 0.84 0.91",
            bottomcolor = "0.74 0.84 0.91"
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
            text = "1 rd",
            posx =  "0.0",
            posy =  "0.02",
            align = "center",
            sizex = "0.065",
            sizey = "0.065",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    countdownText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "THEBOLDFONT",
            text = "GO!",
            posx =  "0",
            posy =  ".3",
            align = "center",
            sizex = "0.15",
            sizey = "0.15",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    velocityText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "SPEEDONE",
            text = "0",
            posx =  "-0.48",
            posy =  ".93",
            align = "left",
            sizex = "0.05",
            sizey = "0.05",
            topcolor = "1.0 0.0 0.265",
            bottomcolor = "1.0 0.0 0.265",
        }
    }
    velocityAddedText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "SPEEDONE",
            text = "km/h",
            posx =  "-0.385",
            posy =  ".945",
            align = "left",
            sizex = "0.03",
            sizey = "0.03",
            topcolor = "1.0 0.0 0.265",
            bottomcolor = "1.0 0.0 0.265",
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
NewWater = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "WaterPlane.mesh",
        static = ""
    },
    RigidBodyComponent = {
        mass = 0,
        isTrigger = ""
    },
    Water = {
    }
}
--wall00 = {
--    Transform = {
--        position = "0 -6 0",
--        rotation = "0 0 0",
--        scale = "1 1 1"
--    },
--    MeshRenderer = {
--        file =  "Wall.00.mesh",
--        static = "",
--        invisible = ""
--    },
--    RigidBodyComponent = {
--        mass = 0,
--        friction = "0.0"
--    }
--}
--wall01 = {
--    Transform = {
--        position = "0 -6 0",
--        rotation = "0 0 0",
--        scale = "1 1 1"
--    },
--    MeshRenderer = {
--        file =  "Wall.01.mesh",
--        static = "",
--        invisible = ""
--    },
--    RigidBodyComponent = {
--        mass = 0,
--        friction = "0.0"
--    }
--}
entities = { "coche", "cocheDos", "mainCam", "secondCam", "velocityText", "consoleDebug", "Test_Track_00", "portrait01Img", "portrait02Img", "counter01Text",
"Road00", "Road01", "Road02", "Road03", "Beach", 
"Terrain00", "Terrain01", "Terrain02", "Terrain03", "waterPlane",
"turbo00", "wall00", "wall01", "NewWater", "UnderWater",
"counter02Text", "SkyboxMeshNew", "raceManager", "tube", "EnemyCar02", "EnemyCar01", "EnemyCar02", "EnemyCar03", "Roads", "positionText", "Extras",
"lapsText", "positionText", "countdownText", "velocityText", "velocityAddedText", "timerText", "laptimerText",}