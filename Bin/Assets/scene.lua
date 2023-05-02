
coche = {
    Transform = {
        position = "0 60 0",
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
    }
}
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
        }
    }

    Area01_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadBorder.mesh"
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
            file =  "Area02_RoadBorder.mesh"
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
            file =  "Area03_RoadBorder.mesh"
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
        main = ""
    },
    AudioListener = {}
}

entities = { "coche", "mainCam", 
            "Area01_RoadMain", "Area01_RoadBorder", "Area01_Vegetation", "Area01_Extra", "Area01_Terrain",
            "Area02_RoadMain", "Area02_RoadBorder", "Area02_Extra",
            "Area03_RoadMain", "Area03_RoadBorder", "Area03_Vegetation", "Area03_Extra", "Area03_Terrain"
        
        }