# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Student_2\Desktop\Timer_lab\Timer_lab_Kunc.cydsn\Timer_lab_Kunc.cyprj
# Date: Wed, 09 Oct 2019 06:40:56 GMT
#set_units -time ns
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 480001 960001} [list [get_pins {ClockBlock/udb_div_0}]]


# Component constraints for C:\Users\Student_2\Desktop\Timer_lab\Timer_lab_Kunc.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Student_2\Desktop\Timer_lab\Timer_lab_Kunc.cydsn\Timer_lab_Kunc.cyprj
# Date: Wed, 09 Oct 2019 06:40:52 GMT
