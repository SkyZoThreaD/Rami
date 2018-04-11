##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug_Win32
ProjectName            :=Rami
ConfigurationName      :=Debug_Win32
WorkspacePath          :=C:/Users/tupac/Documents/Rami
ProjectPath            :=C:/Users/tupac/Documents/Rami
IntermediateDirectory  :=./Debug/
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=tupac
Date                   :=11/04/2018
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :="C:/Program Files/Mingw5/bin/g++.exe"
SharedObjectLinkerName :="C:/Program Files/Mingw5/bin/g++.exe" -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=Rami
Preprocessors          :=$(PreprocessorSwitch)_DEBUG $(PreprocessorSwitch)_CONSOLE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Rami.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :="C:/Program Files/Mingw5/bin/windres.exe"
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)C:/irrlicht-1.8.4/include $(IncludeSwitch)/usr/include/irrlicht/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)Irrlicht 
ArLibs                 :=  "Irrlicht" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:\irrlicht-1.8.4\lib\Win32-gcc $(LibraryPathSwitch)..\..\lib\Win32-gcc 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := "C:/Program Files/Mingw5/bin/ar.exe" rcu
CXX      := "C:/Program Files/Mingw5/bin/g++.exe"
CC       := "C:/Program Files/Mingw5/bin/gcc.exe"
CXXFLAGS :=  -std=c++14 -Wall -g -Wall -fpermissive $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := "C:/Program Files/Mingw5/bin/as.exe"


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
VS_Configuration:=Debug
VS_IntDir:=./Debug/
VS_OutDir:=.
VS_Platform:=Win32
VS_ProjectDir:=/home/tupac/Rami/
VS_ProjectName:=Rami
VS_SolutionDir:=/home/tupac/Rami/
Objects0=$(IntermediateDirectory)/CardType.cpp$(ObjectSuffix) $(IntermediateDirectory)/CardStack.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug/"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug/"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/CardType.cpp$(ObjectSuffix): CardType.cpp $(IntermediateDirectory)/CardType.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/tupac/Documents/Rami/CardType.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CardType.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CardType.cpp$(DependSuffix): CardType.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CardType.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CardType.cpp$(DependSuffix) -MM CardType.cpp

$(IntermediateDirectory)/CardType.cpp$(PreprocessSuffix): CardType.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CardType.cpp$(PreprocessSuffix) CardType.cpp

$(IntermediateDirectory)/CardStack.cpp$(ObjectSuffix): CardStack.cpp $(IntermediateDirectory)/CardStack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/tupac/Documents/Rami/CardStack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CardStack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CardStack.cpp$(DependSuffix): CardStack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CardStack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CardStack.cpp$(DependSuffix) -MM CardStack.cpp

$(IntermediateDirectory)/CardStack.cpp$(PreprocessSuffix): CardStack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CardStack.cpp$(PreprocessSuffix) CardStack.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/tupac/Documents/Rami/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


