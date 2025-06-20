# Simple makefile for assembling and linking a GB program.
rwildcard		=	$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
ASM				:=	rgbasm
LINKER			:=	rgblink
FIX				:=	rgbfix
BUILD_DIR		:=	build
PROJECT_NAME	?=	gb-platformer
OUTPUT			:=	$(PROJECT_NAME)
SRC_DIR			:=	src
INC_DIR			:=	include/
SRC_Z80			:=	$(call rwildcard, $(SRC_DIR)/, *.z80)
OBJ_FILES		:=	$(addprefix $(BUILD_DIR)/obj/, $(SRC_Z80:src/%.z80=%.o))
SYM_FILES		:=	$(addprefix $(BUILD_DIR)/obj/, $(SRC_Z80:src/%.z80=%.sym))
OBJ_DIRS 		:=	$(sort $(addprefix $(BUILD_DIR)/obj/, $(dir $(SRC_Z80:src/%.z80=%.o))))
ASM_FLAGS		:=	-i $(INC_DIR)

.PHONY: all clean

all: fix
	
fix: build
	$(FIX) -m 0x01 -p255 -v -c $(OUTPUT).gb

build: $(OBJ_FILES)
	$(LINKER) --sym $(PROJECT_NAME).sym -o  $(OUTPUT).gb $(OBJ_FILES)
	
$(BUILD_DIR)/obj/%.o : src/%.z80 | $(OBJ_DIRS)
	$(ASM) $(ASM_FLAGS) -o $@ $<

$(OBJ_DIRS): 
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

print-%  : ; @echo $* = $($*)