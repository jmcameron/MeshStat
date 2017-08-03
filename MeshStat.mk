##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=MeshStat
ConfigurationName      :=Debug
WorkspacePath          := "/home/jmcameron/src/MeshStat"
ProjectPath            := "/home/jmcameron/src/MeshStat/MeshStat"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jonathan Cameron
Date                   :=22/07/17
CodeLitePath           :="/home/jmcameron/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="MeshStat.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config --libs --debug)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(shell wx-config --cflags --debug) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/Node.cpp$(ObjectSuffix) $(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix) $(IntermediateDirectory)/NodeUtils.cpp$(ObjectSuffix) $(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IntermediateDirectory)/ini.c$(ObjectSuffix) 


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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM "MainFrame.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) "MainFrame.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/Node.cpp$(ObjectSuffix): Node.cpp $(IntermediateDirectory)/Node.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/Node.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Node.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Node.cpp$(DependSuffix): Node.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Node.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Node.cpp$(DependSuffix) -MM "Node.cpp"

$(IntermediateDirectory)/Node.cpp$(PreprocessSuffix): Node.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Node.cpp$(PreprocessSuffix) "Node.cpp"

$(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix): NodeDisplay.cpp $(IntermediateDirectory)/NodeDisplay.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/NodeDisplay.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NodeDisplay.cpp$(DependSuffix): NodeDisplay.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NodeDisplay.cpp$(DependSuffix) -MM "NodeDisplay.cpp"

$(IntermediateDirectory)/NodeDisplay.cpp$(PreprocessSuffix): NodeDisplay.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NodeDisplay.cpp$(PreprocessSuffix) "NodeDisplay.cpp"

$(IntermediateDirectory)/NodeUtils.cpp$(ObjectSuffix): NodeUtils.cpp $(IntermediateDirectory)/NodeUtils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/NodeUtils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NodeUtils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NodeUtils.cpp$(DependSuffix): NodeUtils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NodeUtils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NodeUtils.cpp$(DependSuffix) -MM "NodeUtils.cpp"

$(IntermediateDirectory)/NodeUtils.cpp$(PreprocessSuffix): NodeUtils.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NodeUtils.cpp$(PreprocessSuffix) "NodeUtils.cpp"

$(IntermediateDirectory)/Config.cpp$(ObjectSuffix): Config.cpp $(IntermediateDirectory)/Config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/Config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Config.cpp$(DependSuffix): Config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Config.cpp$(DependSuffix) -MM "Config.cpp"

$(IntermediateDirectory)/Config.cpp$(PreprocessSuffix): Config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Config.cpp$(PreprocessSuffix) "Config.cpp"

$(IntermediateDirectory)/ini.c$(ObjectSuffix): inih/ini.c $(IntermediateDirectory)/ini.c$(DependSuffix)
	$(CXX) $(IncludePCH) -I inih $(SourceSwitch) "/home/jmcameron/src/MeshStat/MeshStat/inih/ini.c" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ini.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ini.c$(DependSuffix): inih/ini.c
	@$(CXX) $(CXXFLAGS) -I inih $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ini.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ini.c$(DependSuffix) -MM "inih/ini.c"

$(IntermediateDirectory)/ini.c$(PreprocessSuffix): inih/ini.c
	$(CXX) $(CXXFLAGS) $(IncludePCH) -I inih $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ini.c$(PreprocessSuffix) "inih/ini.c"



-include $(IntermediateDirectory)/*$(DependSuffix)


tests: $(OutputFile)
	(cd test; dtest)


##
## Clean
##
clean:
	$(RM) -r ./Debug/


