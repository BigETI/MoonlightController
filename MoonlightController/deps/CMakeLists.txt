include (FetchContent)

set (FETCHCONTENT_QUIET FALSE)

#########
#       #
#  Lua  #
#       #
#########

FetchContent_Declare (Lua
	GIT_REPOSITORY "https://github.com/walterschell/Lua.git"
	GIT_TAG "master"
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable (Lua)
