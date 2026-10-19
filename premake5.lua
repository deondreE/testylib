workspace "TestyLib"
   configurations { "Debug", "Release" }

project "TestyLib"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.hpp", "**.cpp", "**.spec", "**.enbf" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"