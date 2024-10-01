# Set the project type to an application (for executables)
TEMPLATE = app

# Name of the target executable
TARGET = Monopoly

# Specify the Qt modules required
QT += core gui widgets

# Add the source files (.cpp files)
SOURCES += main.cpp \
           board.cpp \
           card.cpp \
           dice.cpp \
           game.cpp \
           player.cpp \
           property.cpp

# Add the header files (.h files)
HEADERS += board.hpp \
           card.hpp \
           dice.hpp \
           game.hpp \
           player.hpp \
           property.hpp

# Include any UI files if needed (e.g., .ui files from Qt Designer)
# FORMS += mainwindow.ui

# Specify the resource file if using Qt resource system (e.g., images, icons)
# RESOURCES += resources.qrc


# Define the output directory
DESTDIR = ./bin

# Set the C++ version
CONFIG += c++11

# For macOS, specify the framework paths if needed
mac {
    INCLUDEPATH += /Users/roeibiton/Qt/6.5.3/macos/include
    LIBS += -L/Users/roeibiton/Qt/6.5.3/macos/lib
}
