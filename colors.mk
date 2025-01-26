COLOR ?= 1
STYLE ?= 1

# Only define colors if COLOR is enabled (1)
ifeq ($(COLOR),1)
# clear resets color and style back to defaults
clear := \e[0m

# no_color clears the foreground color
no_color := \e[39m

# normal colors
red := \e[31m
green := \e[32m
yellow := \e[33m
blue := \e[34m
magenta := \e[35m
cyan := \e[36m
white := \e[37m

# light colors
lt_red := \e[91m
lt_green := \e[92m
lt_yellow := \e[93m
lt_blue := \e[94m
lt_magenta := \e[95m
lt_cyan := \e[96m
lt_white := \e[97m

# background colors
bg_red := \e[41m
bg_green := \e[42m
bg_yellow := \e[43m
bg_blue := \e[44m
bg_magenta := \e[45m
bg_cyan := \e[46m
bg_white := \e[47m

color256 = \e[38;5;$1m

endif

# Only define styles if STYLE is enabled (1)
ifeq ($(STYLE),1)
# clear resets color and style back to defaults
clear := \e[0m

# normal clears dim, bold, and underline
normal := \e[21m\e[22m\e[24m

# styles
dim := \e[2m
bold := \e[1m
uline := \e[4m
endif
