
# Debug or Release
ConfigurationName :=Release

ifeq ($(ConfigurationName),Debug)
  WXDIR=/opt/wx/wxWidgets-3.1.0/build_debug
  WXCONFIGFLAGS=--debug
  SharedObjectLinkerName:=g++ -shared -fPIC
endif
ifeq ($(ConfigurationName),Release)
  WXDIR=/opt/wx/wxWidgets-3.1.0/build_static
  WXCONFIGFLAGS=--static
  SharedObjectLinkerName:=g++ -static -fPIC
endif

ProjectName            :=MeshStat
WorkspacePath          := ""
ProjectPath            := "."
IntermediateDirectory  :=./$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jonathan Cameron
Date                   :=22/07/17
CodeLitePath           :="/home/jmcameron/.codelite"
LinkerName             :=g++
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
IncludePath            := $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 
LinkOptions            := $(shell $(WXDIR)/wx-config --libs $(WXCONFIGFLAGS))

# X86DIR=/usr/lib/x86_64-linux-gnu
# 
# ifeq ($(ConfigurationName),Release)
#   LinkOptions += \
# 	$(X86DIR)/libXxf86vm.a \
# 	$(X86DIR)/libX11.a \
# 	$(X86DIR)/libgdk-x11-2.0.a \
# 	$(X86DIR)/libgtk-x11-2.0.a \
# 	$(X86DIR)/libcairo.a \
# 	$(X86DIR)/libpango-1.0.a \
# 	$(X86DIR)/libpangocairo-1.0.a \
# 	$(X86DIR)/libSM.a \
# 	$(X86DIR)/libpcre.a \
# 	$(X86DIR)/lib*.a
# 
# endif


##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -DINI_HANDLER_LINENO=1 -std=c++11 -Wall $(shell $(WXDIR)/wx-config --cflags $(WXCONFIGFLAGS)) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/Node.cpp$(ObjectSuffix) $(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix) $(IntermediateDirectory)/NodeDisplayPane.cpp$(ObjectSuffix) $(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IntermediateDirectory)/ColorInterpolate.cpp$(ObjectSuffix) $(IntermediateDirectory)/ini.c$(ObjectSuffix) 

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
	@test -d  $(IntermediateDirectory) || $(MakeDirCommand)  $(IntermediateDirectory)


$(IntermediateDirectory)/.d:
	@test -d  $(IntermediateDirectory) || $(MakeDirCommand)  $(IntermediateDirectory)

PreBuild:

##
## Objects
##

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM "MainFrame.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) "MainFrame.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) "wxcrafter.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) "wxcrafter_bitmaps.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/Node.cpp$(ObjectSuffix): Node.cpp $(IntermediateDirectory)/Node.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Node.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Node.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Node.cpp$(DependSuffix): Node.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Node.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Node.cpp$(DependSuffix) -MM "Node.cpp"

$(IntermediateDirectory)/Node.cpp$(PreprocessSuffix): Node.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Node.cpp$(PreprocessSuffix) "Node.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix): NodeDisplay.cpp $(IntermediateDirectory)/NodeDisplay.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "NodeDisplay.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NodeDisplay.cpp$(DependSuffix): NodeDisplay.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NodeDisplay.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NodeDisplay.cpp$(DependSuffix) -MM "NodeDisplay.cpp"

$(IntermediateDirectory)/NodeDisplay.cpp$(PreprocessSuffix): NodeDisplay.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NodeDisplay.cpp$(PreprocessSuffix) "NodeDisplay.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/NodeDisplayPane.cpp$(ObjectSuffix): NodeDisplayPane.cpp $(IntermediateDirectory)/NodeDisplayPane.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "NodeDisplayPane.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NodeDisplayPane.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NodeDisplayPane.cpp$(DependSuffix): NodeDisplayPane.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NodeDisplayPane.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NodeDisplayPane.cpp$(DependSuffix) -MM "NodeDisplayPane.cpp"

$(IntermediateDirectory)/NodeDisplayPane.cpp$(PreprocessSuffix): NodeDisplayPane.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NodeDisplayPane.cpp$(PreprocessSuffix) "NodeDisplayPane.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/Config.cpp$(ObjectSuffix): Config.cpp $(IntermediateDirectory)/Config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "Config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Config.cpp$(DependSuffix): Config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Config.cpp$(DependSuffix) -MM "Config.cpp"

$(IntermediateDirectory)/Config.cpp$(PreprocessSuffix): Config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Config.cpp$(PreprocessSuffix) "Config.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/ColorInterpolate.cpp$(ObjectSuffix): ColorInterpolate.cpp $(IntermediateDirectory)/ColorInterpolate.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "ColorInterpolate.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ColorInterpolate.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ColorInterpolate.cpp$(DependSuffix): ColorInterpolate.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ColorInterpolate.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ColorInterpolate.cpp$(DependSuffix) -MM "ColorInterpolate.cpp"

$(IntermediateDirectory)/ColorInterpolate.cpp$(PreprocessSuffix): ColorInterpolate.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ColorInterpolate.cpp$(PreprocessSuffix) "ColorInterpolate.cpp"

# ----------------------------------------------------------------------

$(IntermediateDirectory)/ini.c$(ObjectSuffix): inih/ini.c $(IntermediateDirectory)/ini.c$(DependSuffix)
	$(CXX) $(IncludePCH) -I inih $(SourceSwitch) "inih/ini.c" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ini.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ini.c$(DependSuffix): inih/ini.c
	@$(CXX) $(CXXFLAGS) -I inih $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ini.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ini.c$(DependSuffix) -MM "inih/ini.c"

$(IntermediateDirectory)/ini.c$(PreprocessSuffix): inih/ini.c
	$(CXX) $(CXXFLAGS) $(IncludePCH) -I inih $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ini.c$(PreprocessSuffix) "inih/ini.c"



-include $(IntermediateDirectory)/*$(DependSuffix)


tests: $(OutputFile)
	(cd test; dtest)


include version.make

dist: all
	@echo
	cp $(IntermediateDirectory)/MeshStat .
	strip MeshStat
	@rm -f MeshStat-linux-$(MESHSTAT_VERSION).zip
	7z a MeshStat-linux-$(MESHSTAT_VERSION).zip MeshStat README.md Releases.txt Sample-MeshStat.ini
	@rm MeshStat
	@echo 
	@echo DONE: Created MeshStat-linux-$(MESHSTAT_VERSION).zip
	@echo

upload: all
	scp MeshStat-*.zip jmcameron:"webapps/jmcameron/mesh/"
	ssh jmcameron "chmod 644 webapps/jmcameron/mesh/MeshStat*.zip"
	ssh jmcameron ls -l "webapps/jmcameron/mesh/MeshStat*.zip"

##
## Clean
##
clean:
	$(RM) -r  $(IntermediateDirectory)/
