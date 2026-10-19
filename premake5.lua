workspace "TestyLib"
   configurations { "Debug", "Release" }

   cppdialect "C++23"

project "TestyLib"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.hpp", "src/**.cpp", "**.spec", "**.enbf", "readme.md" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"