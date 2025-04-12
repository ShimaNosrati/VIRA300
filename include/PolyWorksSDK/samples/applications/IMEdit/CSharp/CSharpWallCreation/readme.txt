This application launches a series of commands to read a pol model
file into PolyWorks|Modeler, and performs a wall creation.

The goodies\PolyWorksSDK\samples\data directory contains appropriate pol files.

For more details, please refer to section 1, "Developing External Modules", of the
PolyWorks SDK Reference Guide in the documentation directory.

This sample code was developed and tested with
Microsoft Visual Studio 2013 and 2017.

Changes note:

If you built your own application based on an earlier version of this framework, we recommend that you use
a file differences tracking tool (such as WinDiff or Araxis Merge) to compare the content of this version
of the framework with the content of the framework you used to build you application. This way, you'll better
be able to see what part of the code was changed and decide whether you want to apply similar changes to
your own application.

Changes in V2021 IR4:

Added a COM Message Filter to prevent COM calls from being rejected if the server application is temporarily busy.

Changes in V2019:

Added Visual C# 2017 support by including .csproj project file.
Visual C# 2013 support is still available through .csproj project file, warnings might appear.
Removed Visual C# 2010 support.
