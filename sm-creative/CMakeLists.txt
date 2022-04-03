# CMakeList.txt : CMake project for sm-creative, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(APP_NAME "sm-creative")

file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/header/*.hpp"
)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/header")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
link_directories("${PROJECT_SOURCE_DIR}/lib") # CMAKE_CURRENT_SOURCE_DIR ????

# Add source to this project's executable.
add_executable (${APP_NAME} "main.cpp" "main.h" ${HEADER_FILES} ${SOURCE_FILES} "include/SFML/Audio.hpp" "include/SFML/Config.hpp" "include/SFML/GpuPreference.hpp" "include/SFML/Graphics.hpp" "include/SFML/Main.hpp" "include/SFML/Network.hpp" "include/SFML/OpenGL.hpp" "include/SFML/System.hpp" "include/SFML/Window.hpp" "include/SFML/Audio/AlResource.hpp" "include/SFML/Audio/Export.hpp" "include/SFML/Audio/InputSoundFile.hpp" "include/SFML/Audio/Listener.hpp" "include/SFML/Audio/Music.hpp" "include/SFML/Audio/OutputSoundFile.hpp" "include/SFML/Audio/Sound.hpp" "include/SFML/Audio/SoundBuffer.hpp" "include/SFML/Audio/SoundBufferRecorder.hpp" "include/SFML/Audio/SoundFileFactory.hpp" "include/SFML/Audio/SoundFileReader.hpp" "include/SFML/Audio/SoundFileWriter.hpp" "include/SFML/Audio/SoundRecorder.hpp" "include/SFML/Audio/SoundSource.hpp" "include/SFML/Audio/SoundStream.hpp" "include/SFML/Graphics/BlendMode.hpp" "include/SFML/Graphics/CircleShape.hpp" "include/SFML/Graphics/Color.hpp" "include/SFML/Graphics/ConvexShape.hpp" "include/SFML/Graphics/Drawable.hpp" "include/SFML/Graphics/Export.hpp" "include/SFML/Graphics/Font.hpp" "include/SFML/Graphics/Glsl.hpp" "include/SFML/Graphics/Glyph.hpp" "include/SFML/Graphics/Image.hpp" "include/SFML/Graphics/PrimitiveType.hpp" "include/SFML/Graphics/Rect.hpp" "include/SFML/Graphics/RectangleShape.hpp" "include/SFML/Graphics/RenderStates.hpp" "include/SFML/Graphics/RenderTarget.hpp" "include/SFML/Graphics/RenderTexture.hpp" "include/SFML/Graphics/RenderWindow.hpp" "include/SFML/Graphics/Shader.hpp" "include/SFML/Graphics/Shape.hpp" "include/SFML/Graphics/Sprite.hpp" "include/SFML/Graphics/Text.hpp" "include/SFML/Graphics/Texture.hpp" "include/SFML/Graphics/Transform.hpp" "include/SFML/Graphics/Transformable.hpp" "include/SFML/Graphics/Vertex.hpp" "include/SFML/Graphics/VertexArray.hpp" "include/SFML/Graphics/VertexBuffer.hpp" "include/SFML/Graphics/View.hpp" "include/SFML/Network/Export.hpp" "include/SFML/Network/Ftp.hpp" "include/SFML/Network/Http.hpp" "include/SFML/Network/IpAddress.hpp" "include/SFML/Network/Packet.hpp" "include/SFML/Network/Socket.hpp" "include/SFML/Network/SocketHandle.hpp" "include/SFML/Network/SocketSelector.hpp" "include/SFML/Network/TcpListener.hpp" "include/SFML/Network/TcpSocket.hpp" "include/SFML/Network/UdpSocket.hpp" "include/SFML/System/Clock.hpp" "include/SFML/System/Err.hpp" "include/SFML/System/Export.hpp" "include/SFML/System/FileInputStream.hpp" "include/SFML/System/InputStream.hpp" "include/SFML/System/Lock.hpp" "include/SFML/System/MemoryInputStream.hpp" "include/SFML/System/Mutex.hpp" "include/SFML/System/NativeActivity.hpp" "include/SFML/System/NonCopyable.hpp" "include/SFML/System/Sleep.hpp" "include/SFML/System/String.hpp" "include/SFML/System/Thread.hpp" "include/SFML/System/ThreadLocal.hpp" "include/SFML/System/ThreadLocalPtr.hpp" "include/SFML/System/Time.hpp" "include/SFML/System/Utf.hpp" "include/SFML/System/Vector2.hpp" "include/SFML/System/Vector3.hpp" "include/SFML/Window/Clipboard.hpp" "include/SFML/Window/Context.hpp" "include/SFML/Window/ContextSettings.hpp" "include/SFML/Window/Cursor.hpp" "include/SFML/Window/Event.hpp" "include/SFML/Window/Export.hpp" "include/SFML/Window/GlResource.hpp" "include/SFML/Window/Joystick.hpp" "include/SFML/Window/Keyboard.hpp" "include/SFML/Window/Mouse.hpp" "include/SFML/Window/Sensor.hpp" "include/SFML/Window/Touch.hpp" "include/SFML/Window/VideoMode.hpp" "include/SFML/Window/Window.hpp" "include/SFML/Window/WindowHandle.hpp" "include/SFML/Window/WindowStyle.hpp"
# "header/root.h" "header/natives.h" "header/types.h" "header/Animation.h" "src/Animation.cpp" "header/world/Level.h" "src/world/Level.cpp" "header/Assets.h" "header/world/WorldTile.h" "src/world/WorldTile.cpp" "header/utils/FpsCounter.h" "src/utils/FpsCounter.cpp" "header/world.h" "header/Tile.h" "src/Tile.cpp" "src/Assets.cpp" "src/utils/files.cpp"  "header/utils/files.h" "header/mobs/Mob.h" "src/mobs/Mob.cpp" "header/mobs/Player.h" "src/mobs/Player.cpp" "header/constants.h"  "header/player/Camera.h" "src/player/Camera.cpp" "header/game/Game.h" "src/game/Game.cpp" "header/game/screens/ScreenLevel.h" "src/game/screens/ScreenLevel.cpp" "header/game/Collider.h" "src/game/Collider.cpp"
 "header/physics/Collision.h" "src/physics/Collision.cpp")

# target_link_libraries(${APP_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/*.lib")
target_link_libraries(${APP_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/sfml-system-d.lib")
target_link_libraries(${APP_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/sfml-graphics-d.lib")
target_link_libraries(${APP_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/sfml-audio-d.lib")
target_link_libraries(${APP_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/sfml-network-d.lib")
target_link_libraries(${APP_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/sfml-window-d.lib")
target_include_directories(${APP_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# copy the contents of the "res" file directly into the binary folder.
add_custom_command(
    TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "${CMAKE_CURRENT_BINARY_DIR}/res"
)

# TODO: Add tests and install targets if needed.
