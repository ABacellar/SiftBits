APP = sensors

include $(SDK_DIR)/Makefile.defs

OBJS = $(ASSETS).gen.o main.o Component.o QBit.o Gate.o Sensor.o QState.o
ASSETDEPS += *.png $(ASSETS).lua
CCFLAGS += -DCUBE_ALLOCATION=24

# build assets.html to proof stir-processed assets.
# comment out to disable.
ASSETS_BUILD_PROOF := yes

include $(SDK_DIR)/Makefile.rules
