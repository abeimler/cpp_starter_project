# Set this to the minimal version you want to support
find_package(raylib 2.5 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY  https://github.com/raysan5/raylib.git
    GIT_TAG         2.5.0
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
    if(BUILD_ON_RASPBERRY_PI) # set platform for RPI
      set(PLATFORM "Raspberry Pi" CACHE STRING "" FORCE)
    endif()

    ## disable/enable features by default
    #set(USE_AUDIO                   OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_ASTC     OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_DDS      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_FNT      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_GLTF     OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_HDR      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_IQM      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_KTX      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_OBJ      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_XM       OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_MP3      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_OGG      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_WAV      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_MOD      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_MTL      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_FILEFORMAT_TTF      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_IMAGE_GENERATION    OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_IMAGE_EXPORT        OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_IMAGE_MANIPULATION  OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_MESH_GENERATION     OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_CAMERA_SYSTEM       OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_MOUSE_GESTURES      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_GIF_RECORDING       OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_SCREEN_CAPTURE      OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_VR_SIMULATOR        OFF CACHE BOOL "" FORCE)
    #set(SUPPORT_GESTURES_SYSTEM     OFF CACHE BOOL "" FORCE)

    if(NOT ENABLE_LOGGING)
    set(SUPPORT_TRACELOG            OFF CACHE BOOL "" FORCE)
    endif()

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()
