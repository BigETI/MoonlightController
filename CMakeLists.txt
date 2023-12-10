cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
	cmake_policy (SET CMP0141 NEW)
	set (CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

##########################
#                        #
#  Moonlight Controller  #
#                        #
##########################

project (MoonlightController
	VERSION "0.0.0"
	DESCRIPTION "Moonlight Controller Library"
)

add_subdirectory ("MoonlightController")

##############################
#                            #
#  Moonlight Controller CLI  #
#                            #
##############################

project (MoonlightControllerCLI
	VERSION "0.0.0"
	DESCRIPTION "Moonlight Controller CLI Application"
)

add_subdirectory ("MoonlightControllerCLI")
