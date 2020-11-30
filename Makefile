# Exported from https://tiplanet.org/pb/ on Mon Nov 30 21:07:56 2020 (CET)

# ----------------------------
# Program Options
# ----------------------------

NAME         ?= STORYCE
ICON         ?= icon.png
DESCRIPTION  ?= "Story game CE"
COMPRESSED   ?= YES
ARCHIVED     ?= YES

# ----------------------------
# Compile Options
# ----------------------------

CFLAGS ?= -Oz -W -Wall -Wwrite-strings -Wno-unknown-pragmas -Wno-incompatible-library-redeclaration -Wno-main-return-type
CXXFLAGS ?= -Oz -W -Wall -Wwrite-strings -Wno-unknown-pragmas -Wno-incompatible-library-redeclaration -Wno-main-return-type -fno-exceptions

# ----------------------------
# Debug Options
# ----------------------------

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
