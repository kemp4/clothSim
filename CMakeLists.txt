cmake_minimum_required(VERSION 3.12)
project(cars)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


add_executable(cars
        src/Objects/AbstractGameObject.cpp
        src/Objects/AbstractGameObject.h
        src/Objects/Camera.cpp
        src/Objects/Camera.h
        src/ExampleGame.cpp
        src/ExampleGame.h
        src/Game.cpp
        src/Game.h
        src/Main.cpp
        src/Main.h
        src/GUI/NkWindow.cpp
        src/GUI/NkWindow.h
        src/GUI/nuklear.h
        src/GUI/nuklear_glfw_gl3.h
        src/GUI/Options.cpp
        src/GUI/Options.h
        src/ResoureManagment/ResourceManager.cpp
        src/ResoureManagment/ResourceManager.h
        src/ResoureManagment/Shader.cpp
        src/ResoureManagment/Shader.h
        src/Objects/SimpleObject.cpp
        src/Objects/SimpleObject.h
        src/baseHeader.h
        src/ResoureManagment/Texture.cpp
        src/ResoureManagment/Texture.h
        src/ResoureManagment/VaoObject.cpp
        src/ResoureManagment/VaoObject.h
        src/ResoureManagment/SOIL.h
        src/Objects/NonPlayerObject.cpp
        src/Objects/NonPlayerObject.h
        src/Objects/Enemy.cpp
        src/Objects/Enemy.h src/Objects/Particle/ParticleSystem.cpp src/Objects/Particle/ParticleSystem.h src/Objects/Particle/Particle.cpp src/Objects/Particle/Particle.h)
target_link_libraries(cars -lglut -lGL -lGLU -lGLEW -lglfw -lSOIL)