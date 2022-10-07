#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-LPCUSBDK_16F1455.mk)" "nbproject/Makefile-local-LPCUSBDK_16F1455.mk"
include nbproject/Makefile-local-LPCUSBDK_16F1455.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=LPCUSBDK_16F1455
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lib/usb/usb_descriptors.c lib/usb/usb_device.c lib/usb/usb_device_hid.c lib/usb/usb_events.c main.c lib/app_device_joystick.c lib/app_led_usb_status.c lib/buttons.c lib/leds.c lib/system.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib/usb/usb_descriptors.p1 ${OBJECTDIR}/lib/usb/usb_device.p1 ${OBJECTDIR}/lib/usb/usb_device_hid.p1 ${OBJECTDIR}/lib/usb/usb_events.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/lib/app_device_joystick.p1 ${OBJECTDIR}/lib/app_led_usb_status.p1 ${OBJECTDIR}/lib/buttons.p1 ${OBJECTDIR}/lib/leds.p1 ${OBJECTDIR}/lib/system.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/lib/usb/usb_descriptors.p1.d ${OBJECTDIR}/lib/usb/usb_device.p1.d ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d ${OBJECTDIR}/lib/usb/usb_events.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/lib/app_device_joystick.p1.d ${OBJECTDIR}/lib/app_led_usb_status.p1.d ${OBJECTDIR}/lib/buttons.p1.d ${OBJECTDIR}/lib/leds.p1.d ${OBJECTDIR}/lib/system.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib/usb/usb_descriptors.p1 ${OBJECTDIR}/lib/usb/usb_device.p1 ${OBJECTDIR}/lib/usb/usb_device_hid.p1 ${OBJECTDIR}/lib/usb/usb_events.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/lib/app_device_joystick.p1 ${OBJECTDIR}/lib/app_led_usb_status.p1 ${OBJECTDIR}/lib/buttons.p1 ${OBJECTDIR}/lib/leds.p1 ${OBJECTDIR}/lib/system.p1

# Source Files
SOURCEFILES=lib/usb/usb_descriptors.c lib/usb/usb_device.c lib/usb/usb_device_hid.c lib/usb/usb_events.c main.c lib/app_device_joystick.c lib/app_led_usb_status.c lib/buttons.c lib/leds.c lib/system.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-LPCUSBDK_16F1455.mk ${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F1455
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib/usb/usb_descriptors.p1: lib/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_descriptors.p1 lib/usb/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_descriptors.d ${OBJECTDIR}/lib/usb/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/usb/usb_device.p1: lib/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_device.p1 lib/usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_device.d ${OBJECTDIR}/lib/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/usb/usb_device_hid.p1: lib/usb/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device_hid.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_device_hid.p1 lib/usb/usb_device_hid.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_device_hid.d ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/usb/usb_events.p1: lib/usb/usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_events.p1 lib/usb/usb_events.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_events.d ${OBJECTDIR}/lib/usb/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/app_device_joystick.p1: lib/app_device_joystick.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/app_device_joystick.p1.d 
	@${RM} ${OBJECTDIR}/lib/app_device_joystick.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/app_device_joystick.p1 lib/app_device_joystick.c 
	@-${MV} ${OBJECTDIR}/lib/app_device_joystick.d ${OBJECTDIR}/lib/app_device_joystick.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/app_device_joystick.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/app_led_usb_status.p1: lib/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/lib/app_led_usb_status.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/app_led_usb_status.p1 lib/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/lib/app_led_usb_status.d ${OBJECTDIR}/lib/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/buttons.p1: lib/buttons.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/buttons.p1.d 
	@${RM} ${OBJECTDIR}/lib/buttons.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/buttons.p1 lib/buttons.c 
	@-${MV} ${OBJECTDIR}/lib/buttons.d ${OBJECTDIR}/lib/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/leds.p1: lib/leds.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/leds.p1.d 
	@${RM} ${OBJECTDIR}/lib/leds.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/leds.p1 lib/leds.c 
	@-${MV} ${OBJECTDIR}/lib/leds.d ${OBJECTDIR}/lib/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/system.p1: lib/system.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/system.p1.d 
	@${RM} ${OBJECTDIR}/lib/system.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/system.p1 lib/system.c 
	@-${MV} ${OBJECTDIR}/lib/system.d ${OBJECTDIR}/lib/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/lib/usb/usb_descriptors.p1: lib/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_descriptors.p1 lib/usb/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_descriptors.d ${OBJECTDIR}/lib/usb/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/usb/usb_device.p1: lib/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_device.p1 lib/usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_device.d ${OBJECTDIR}/lib/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/usb/usb_device_hid.p1: lib/usb/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_device_hid.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_device_hid.p1 lib/usb/usb_device_hid.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_device_hid.d ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_device_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/usb/usb_events.p1: lib/usb/usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib/usb" 
	@${RM} ${OBJECTDIR}/lib/usb/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/lib/usb/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/usb/usb_events.p1 lib/usb/usb_events.c 
	@-${MV} ${OBJECTDIR}/lib/usb/usb_events.d ${OBJECTDIR}/lib/usb/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/usb/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/app_device_joystick.p1: lib/app_device_joystick.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/app_device_joystick.p1.d 
	@${RM} ${OBJECTDIR}/lib/app_device_joystick.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/app_device_joystick.p1 lib/app_device_joystick.c 
	@-${MV} ${OBJECTDIR}/lib/app_device_joystick.d ${OBJECTDIR}/lib/app_device_joystick.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/app_device_joystick.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/app_led_usb_status.p1: lib/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/lib/app_led_usb_status.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/app_led_usb_status.p1 lib/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/lib/app_led_usb_status.d ${OBJECTDIR}/lib/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/buttons.p1: lib/buttons.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/buttons.p1.d 
	@${RM} ${OBJECTDIR}/lib/buttons.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/buttons.p1 lib/buttons.c 
	@-${MV} ${OBJECTDIR}/lib/buttons.d ${OBJECTDIR}/lib/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/leds.p1: lib/leds.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/leds.p1.d 
	@${RM} ${OBJECTDIR}/lib/leds.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/leds.p1 lib/leds.c 
	@-${MV} ${OBJECTDIR}/lib/leds.d ${OBJECTDIR}/lib/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib/system.p1: lib/system.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/system.p1.d 
	@${RM} ${OBJECTDIR}/lib/system.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/lib/system.p1 lib/system.c 
	@-${MV} ${OBJECTDIR}/lib/system.d ${OBJECTDIR}/lib/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits -gdwarf-3 -mstack=compiled:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.map  -DXPRJ_LPCUSBDK_16F1455=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -maddrqual=ignore -xassembler-with-cpp -I"../demo_src" -I"../../../../../../framework/usb/inc" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"." -mwarn=0 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mosccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/pic16f1455_firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
