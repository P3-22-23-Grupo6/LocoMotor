
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
        target = "coche" ,
        main = ""
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "0 15 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    PlayerController = {},
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
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
        posx =  "0.45",
        posy =  ".05",
        align = "right",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "0 0 0",
        bottomcolor = "0 0 0",
    },
    RaceManager = {
        checkpoint0 =  "2 1 -8",
        checkpoint1 =  "2 1 -27",
        checkpoint2 =  "2 1 -44",
        checkpoint4 =  "2 1 -8"
    }
}
do ---------------------   UI   ------------------------------
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
    countdownText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "Heavitas",
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
            font =  "BrunoAce",
            text = "100 km/h",
            posx =  "-0.45",
            posy =  ".1",
            align = "left",
            sizex = "0.1",
            sizey = "0.1",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
end ----------------------------------------------------------
do ---------------------   AREA01   ------------------------------
    Area01_RoadMain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadMain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        },
        ParticleSystem = {
            name = "dust",
            file = "Racers/Sparkler"
        }
    }

    Area01_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadBorder.mesh",
            static = ""
        }
    }

    Area01_Vegetation = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Vegetation.mesh",
            static = ""
        }
    }
    Area01_Terrain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Terrain.mesh",
            static = ""
        }
    }
    Area01_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Extra.mesh",
            static = ""
        }
    }

end -------------------------------------------------------------------
do ---------------------   AREA02   ------------------------------
    Area02_RoadMain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_RoadMain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        }
    }

    Area02_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_RoadBorder.mesh",
            static = ""
        }
    }
    Area02_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_Extra.mesh",
            static = ""
        }
    }

end -------------------------------------------------------------------
do ---------------------   AREA03   ------------------------------
    Area03_RoadMain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_RoadMain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        }
    }

    Area03_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_RoadBorder.mesh",
            static = ""
        }
    }

    Area03_Vegetation = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_Vegetation.mesh",
            static = ""
        }
    }
    Area03_Terrain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_Terrain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        }
    }
    Area03_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_Extra.mesh",
            static = ""
        }
    }

end -------------------------------------------------------------------
do ---------------------   AREA04   ------------------------------
    Area04_Vegetation = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area04_Vegetation.mesh",
            static = ""
        }
    }
    Area04_Terrain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area04_Terrain.mesh",
            static = ""
        }
    }
    Area04_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area04_Extra.mesh",
            static = ""
        }
    }
    Area05_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area05_Extra.mesh",
            static = ""
        }
    }
end -------------------------------------------------------------------
do ---------------------   AREA04   ------------------------------
    Area01_RoadWalls = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadWalls.mesh",
            static = "",
            invisible = ""
        },
        RigidBodyComponent = {
            mass = 0,
            friction = "0.0"
        }
    }
    Area02_RoadWalls = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_RoadWalls.mesh",
            static = "",
            invisible = ""
        },
        RigidBodyComponent = {
            mass = 1,
            friction = "0.0"
        }
    }
    Area03_RoadWalls = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_RoadWalls.mesh",
            static = "",
            invisible = ""
        },
        RigidBodyComponent = {
            mass = 1,
            friction = "0.0"
        }
    }
end -------------------------------------------------------------------

Main_Terrain = {
    Transform = {
        position = "0 -6 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Main_Terrain.mesh",
        static = ""
    }
}
Main_Water = {
    Transform = {
        position = "0 -6 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Main_Water.mesh",
        static = ""
    }
}
SkyboxMesh = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "SkyboxMesh.mesh",
        static = ""
    }
}
EnemyCar = {
    Transform = {
        position = "0 15 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "EnemyCar.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "20",
        StartSeparation = "5"
    },
}

entities = { "coche", "mainCam", "raceManager",
            "lapsText", "positionText", "countdownText", "velocityText",
            "Area01_RoadMain", "Area01_RoadBorder", "Area01_Vegetation", "Area01_Extra", "Area01_Terrain",
            "Area02_RoadMain", "Area02_RoadBorder", "Area02_Extra",
            "Area03_RoadMain", "Area03_RoadBorder", "Area03_Vegetation", "Area03_Extra", "Area03_Terrain",
            "Area04_Vegetation", "Area04_Extra", "Area04_Terrain", "Area05_Extra",
            "Area01_RoadWalls", "Area02_RoadWalls", "Area03_RoadWalls",
            "Main_Terrain", "Main_Water", "SkyboxMesh",
            "EnemyCar"
        }