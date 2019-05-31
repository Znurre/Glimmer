QT += gamepad

SOURCES += \
    IslandScoreCallback.cpp \
    LowerScoreClaimCallback.cpp \
    PlayerPlacementCallback.cpp \
    PlayerRematchCallback.cpp \
    ReverseDirectionClaimCallback.cpp \
    SlowTimeClaimCallback.cpp \
    SpawnIslandsClaimCallback.cpp \
    main.cpp \
    Window.cpp \
    Player.cpp \
    World.cpp \
    Island.cpp \
    PlayerSelectionScreen.cpp \
    Stage.cpp \
    GameScreen.cpp \
    TransitionScreen.cpp \
    KeyboardInputMethod.cpp \
    PlayerController.cpp

HEADERS += \
    IIslandClaimCallback.h \
    IPlayerInputCallback.h \
    IslandScoreCallback.h \
    LowerScoreClaimCallback.h \
    PlayerPlacementCallback.h \
    PlayerRematchCallback.h \
    ReverseDirectionClaimCallback.h \
    SlowTimeClaimCallback.h \
    SpawnIslandsClaimCallback.h \
    Window.h \
    Player.h \
    World.h \
    Island.h \
    PlayerSelectionScreen.h \
    IScreen.h \
    Stage.h \
    GameScreen.h \
    Utility.h \
    TransitionScreen.h \
    IInputMethod.h \
    KeyboardInputMethod.h \
    PlayerController.h \
    IPlayerProvider.h
