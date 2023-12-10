##############################
#                            #
#  Moonlight Controller CLI  #
#                            #
##############################

add_executable (MoonlightControllerCLI
	"src/Command.cpp"
	"src/Commands.cpp"
	"src/main.cpp"
)

target_compile_features (MoonlightControllerCLI
	PRIVATE cxx_std_23
)

set_property (TARGET MoonlightControllerCLI
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_compile_definitions (MoonlightControllerCLI
	PRIVATE IS_MOONLIGHT_CONTROLLER_STATIC
)

target_include_directories (MoonlightControllerCLI
	PRIVATE "include"
)

target_link_libraries (MoonlightControllerCLI
	PRIVATE MoonlightControllerStatic
)
