project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		buildoptions { "-std=c11", "-lgdi32" }
		systemversion "10.0.22621.0"
		staticruntime "On"

		
	

	filter { "system:windows", "configurations:Release" }	
		buildoptions "/MT"


	