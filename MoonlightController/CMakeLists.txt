##################################
#                                #
#  Moonlight Controller library  #
#                                #
##################################

##################
#                #
#  Dependencies  #
#                #
##################

add_subdirectory ("deps")

#################################
#                               #
#  Statically linkable library  #
#                               #
#################################

add_library (MoonlightControllerStatic STATIC
	"src/Scripting/Lua/LuaModule.cpp"
	"src/Controllers/XInput/XInputBatteryInformation.cpp"
	"src/Controllers/XInput/XInputCapabilities.cpp"
	"src/Controllers/XInput/XInputKeystroke.cpp"
)

if (WIN32)
	target_sources (MoonlightControllerStatic
		PRIVATE "src/Platforms/Windows/Controllers/Keyboard/KeyboardController.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/Keyboard/KeyboardControllers.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/Mouse/MouseController.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/Mouse/MouseControllers.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/XInput/XInputController.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/XInput/XInputControllers.cpp"
	)
endif()

set_property (TARGET MoonlightControllerStatic
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_compile_features (MoonlightControllerStatic
	PRIVATE cxx_std_23
)

target_compile_definitions (MoonlightControllerStatic
	PRIVATE IS_MOONLIGHT_CONTROLLER_STATIC
)

target_include_directories (MoonlightControllerStatic
	PUBLIC "include"
)

if (WIN32)
	target_link_libraries (MoonlightControllerStatic
		PUBLIC lua_static
		PUBLIC XInput
	)
else ()
	target_link_libraries (MoonlightControllerStatic
		PUBLIC lua_static
	)
endif ()

##################################
#                                #
#  Dynamically linkable library  #
#                                #
##################################

add_library (MoonlightController SHARED
	"src/Scripting/Lua/LuaModule.cpp"
	"src/Controllers/XInput/XInputBatteryInformation.cpp"
	"src/Controllers/XInput/XInputCapabilities.cpp"
	"src/Controllers/XInput/XInputKeystroke.cpp"
)

if (WIN32)
	target_sources (MoonlightController
		PRIVATE "src/Platforms/Windows/Controllers/Keyboard/KeyboardController.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/Keyboard/KeyboardControllers.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/Mouse/MouseController.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/Mouse/MouseControllers.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/XInput/XInputController.cpp"
		PRIVATE "src/Platforms/Windows/Controllers/XInput/XInputControllers.cpp"
	)
endif()

target_compile_features (MoonlightController
	PRIVATE cxx_std_23
)

set_property (TARGET MoonlightController
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_compile_definitions (MoonlightController
	PRIVATE IS_MOONLIGHT_CONTROLLER_EXPORTING
)

target_include_directories (MoonlightController
	PUBLIC "include"
)

if (WIN32)
	target_link_libraries (MoonlightController
		PUBLIC lua_static
		PUBLIC XInput
	)
else ()
	target_link_libraries (MoonlightController
		PUBLIC lua_static
	)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options (MoonlightController
		PRIVATE -fPIC
	)
	add_compile_options (-fPIC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
endif ()
