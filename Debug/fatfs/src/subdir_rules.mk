################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
fatfs/src/%.obj: ../fatfs/src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/Users/ADMIN/workspace_v9/CC_2021_12x" --include_path="C:/Users/ADMIN/workspace_v9/CC_2021_12x/SDCard" --include_path="C:/Users/ADMIN/workspace_v9/CC_2021_12x/fatfs" --include_path="C:/Users/ADMIN/workspace_v9/CC_2021_12x/include" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --preinclude="C:/Users/ADMIN/workspace_v9/CC_2021_12x/fatfs/src/ff.h" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="fatfs/src/$(basename $(<F)).d_raw" --obj_directory="fatfs/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


