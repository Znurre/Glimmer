QT += gamepad

SOURCES += \
    PlayerPlacementCallback.cpp \
    PlayerRematchCallback.cpp \
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
    IPlayerInputCallback.h \
    PlayerPlacementCallback.h \
    PlayerRematchCallback.h \
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
