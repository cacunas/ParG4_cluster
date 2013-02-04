# $Id: GNUmakefile,v 1.2 2010-01-11 16:56:29 gcosmo Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := LYSO
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = /opt/geant4/share/Geant4-9.5.1/geant4make
endif

include ParGNUmakefile

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

ifdef ROOTSYS
CPPFLAGS += -I$(shell $(ROOTSYS)/bin/root-config --incdir)
CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
LDLIBS += $(shell $(ROOTSYS)/bin/root-config --libs)
endif

ifeq ($(G4SYSTEM),Linux-g++)
LDLIBS += -Wl,-rpath,$(shell $(ROOTSYS)/bin/root-config --libdir)
endif
