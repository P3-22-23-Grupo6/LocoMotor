ButtonManager = {
    SceneChangeButton = {},
    AudioSource = {
        vol = "0.2",
        soundDimension = "2D"
    }
}
audioHolder = {
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/MenuMusic.mp3",
        loopStart = "17105",
        loopEnd = "214244",
        soundDimension = "2D",
        vol = "0.2"
    },
}
-- UI PANELS
selectTrackTitle = {
    UIImageLM = { 
        posx = "0",
        posy = "0",
        sizex = "0.24",
        sizey = "0.06",
        img = "m_selectTrakTitle"
    }
}
selectTrackButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.71",
        posy = "0.76",
        sizex = "0.3",
        sizey = "0.22",
        img = "m_select"
    }
}
entities = {"ButtonManager", "MenuDecalMesh", "goToIntroButton", "MenuBackgroundMesh", "falconPreview", "selectTrackTitle", "selectTrackButton",
"mainCam", "logoImg", "menuBack", "audioHolder", "trackArrowLeftButton", "trackArrowRightButton", "trackMesh00", "trackMesh01", "Portrait_Track"}