add_executable(twixt-game main.cpp)

target_compile_features(twixt-game PRIVATE cxx_std_17)

target_link_libraries(twixt-game
    agent game board render
    sfml-graphics sfml-window sfml-system 
    ImGui-SFML::ImGui-SFML
)

target_link_directories(twixt-game INTERFACE ..)