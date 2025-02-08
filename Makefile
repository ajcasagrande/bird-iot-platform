include colors.mk

ifdef debug
SHELL = /bin/bash -x
else
SHELL = /bin/bash
endif

define newline


endef

# kconfig default
default ?= n

# The default flags to use when calling submakes
GNUMAKEFLAGS = --no-print-directory

VERSION_HEADER_FILE = bird_iot/include/version.h
PLUGINS_INC_FILE = bird_iot/include/plugins_inc.h
BASE_VERSION := $(shell git describe --tags --always --dirty | sed -r 's/^v//g')
REVISION := $(shell echo "$$(git rev-parse --abbrev-ref HEAD)-$$(git describe --always --dirty)")
VERSION = $(BASE_VERSION)-$(REVISION)
OLD_REVISION := $(shell sed -nr 's/.*SOFTWARE_REVISION "([^"]+)".*/\1/p' $(VERSION_HEADER_FILE) || echo -n "must-recreate")
SOURCES := $(shell find bird_iot/ -name '*.cpp' -or -name '*.c' -or -name '*.h' -or -name '*.hpp')

ifdef DOCKER_BUILD
activate_venv = true
venv = $1 $(args)
py3 = PYTHONIOENCODING=utf8 python3 $1 $(args)
idf_py = cd $(call project_dir,$1) && idf.py $2 $(args)
idf_size_py = idf_size.py $1 $(args)
else
activate_venv = . ./activate_env
venv = $(activate_venv) && $1 $(args)
py3 = $(activate_venv) && python3 $1 $(args)
idf_py = $(activate_venv) && cd $(call project_dir,$1) && idf.py $2 $(args)
idf_size_py = $(activate_venv) && idf_size.py $1 $(args)
endif

virtualenv = python3 -m venv

py_tools = tools/python
py3_tool = $(call py3,$(py_tools)/$1)
project_dir = projects/$1
output_dir = $(call project_dir,$1)/build
sdkconfig_file = $(call project_dir,$1)/sdkconfig

bump ?= patch
semver = tools/semver-tool/src/semver
get_tag = git describe --abbrev=0 --tags
bump_version = "$$($(semver) bump $1 "$$($(get_tag))")"
tag_version = git tag $1
SNAKE_CASE = $$(echo '$1' | sed -r 's/([A-Z])/_\L\1/g' | sed 's/^_//' | tr '[:lower:]' '[:upper:]')
NameWithSpaces = $$(echo '$1' | sed -r 's/([A-Z])/ \1/g' | sed 's/^ //')
FilterOutPlugin = $$(echo '$1' | sed -r 's/(Plugin|Driver|Sensor|Component|Task)$$//g')
FirstWord = $$(echo "$1" | sed -r 's/([^ ]+) .*/\1/g')

define print_error =
	printf "$(lt_red)┌──────────┐ \
\n│ $(bold)%-8s$(normal) │ \
\n├──────────┴─────────────────────────────────────────────────────────┐ \
\n│ $(bold)$(call color256,109)%-66s$(lt_red) │ \
\n└────────────────────────────────────────────────────────────────────┘ \
\n$(clear)" "ERROR" "$(strip $1)"
endef

define require_args =
@$(foreach arg,$(strip $1), \
	if [ -z "$($(arg))" ]; then \
		$(call print_error,Missing required argument: '$(arg)'); \
		exit 1; \
	fi; \
)
endef

BAUD_RATE ?= 115200
FLASH_BAUD ?= 921600
trap_ctrl_c = trap 'exit 0' INT;

ota_host = localhost
ota_http_port = 9000
ota_https_port = 9001
ota_bearer = TODO_OTA_BEARER_HERE
ota_ca_cert = ../bird-ota/certs/ca.crt

ifdef insecure
ota_base_url = http://$(ota_host):$(ota_http_port)
curl_args = -H "Authorization: Bearer $(ota_bearer)"
else
ota_base_url = https://$(ota_host):$(ota_https_port)
curl_args = -H "Authorization: Bearer $(ota_bearer)" --cacert $(ota_ca_cert)
endif

TTY = /dev/$(port)
tty_by_id = serial/by-id/usb-$(serial_chip)_$1-if00-port0

esp32-f06320 = ttgo-display 0154E557
esp32-998fb4 = ttgo-display 01CA62C1
esp32-f05ff4 = ttgo-display 0154E4A3
esp32-999118 = ttgo-display 01CA6313
esp32-998f60 = ttgo-display 01CA62B1

# Spektrum I2C Slave
esp32-998fec = ttgo-display 01CA62D2

# GPS
esp32-f05e50 = rc-gps 0154E44D

# RC
# Limitless
esp32-f064c0 = rc-lights 0154E5B4

esp32-b6ce6c = lolin32 01BB8C25
esp32-592470 = lolin32 01BB8C29
esp32-5927d4 = lolin32 01BB8CFA
esp32-5a9c14 = lolin32 01BB8E2C
esp32-5986ac = lolin32 01BB89AC
esp32-5940a4 = lolin32 01BB8CFD

# Living Room SHIELD TV
esp32-998aa0 = bt-kb 01CA61AC
esp32-f06858 = bt-kb 0154E679

esp32-75cfb0 = esp32-cam

esp32-4f51e4 = m5-stick B95239C545 Kongou_Hikari_M5Stack_Intf

build_envs = ttgo-display lolin32 bt-kb rc-gps rc-lights m5-stick spektrum
envs = $(build_envs) esp32-cam ttgo-debug
default_env = ttgo-display
channel ?= dev
devices = $(filter esp32-%,$(.VARIABLES))

ifdef id
host ?= $(filter esp32-%$(id),$(devices))
env ?= $(word 1,$($(host)))
serial_id ?= $(word 2,$($(host)))
serial_chip ?= $(if $(word 3,$($(host))),$(word 3,$($(host))),Silicon_Labs_CP2104_USB_to_UART_Bridge_Controller)
# note this requires a udev rule to add a symlink
port ?= $(if $(serial_id),$(call tty_by_id,$(serial_id)),$(host))
else
serial_chip ?= Silicon_Labs_CP2104_USB_to_UART_Bridge_Controller
endif

ifdef p
port = ttyUSB$(p)
# because we no longer have a reverse lookup, if user specifies port number, 
# do NOT set env automatically to prevent flashing wrong env
default_env = 
endif

# default env
ifndef env
env = $(default_env)
endif

define build_template =
$1: $(call output_dir,$1)/$1.bin

endef

define fimrware_template =
$(addprefix $(call output_dir,$1)/$1.,bin elf map): $(addprefix $(call project_dir,$1)/,partitions.csv CMakeLists.txt sdkconfig) bird_iot/CMakeLists.txt $(SOURCES) $(if $(filter-out $(REVISION),$(OLD_REVISION)),update-version-header,)
	$(call idf_py,$1,build)
	cp $(call output_dir,$1)/$1.bin firmware/$1.bin
	$(MAKE) size env=$1

endef

define post_ota =
	@printf "curl -X POST $(ota_base_url)/$1 \n"
	@curl -X POST $(curl_args) "$(ota_base_url)/$1"

endef

define ota_template =
ota-$1: $1
$(if $(filter $(channel),stable),
  $(if $(findstring -dirty,$(REVISION)),
		@printf "$(lt_red) \
\n┌──────────┐ \
\n│ $(bold)%-8s$(normal) │ \
\n├──────────┴─────────────────────────────────────────────────────────┐ \
\n│ $(bold)$(white)%-66s$(normal)$(lt_red) │ \
\n│ $(bold)$(white)%-66s$(normal)$(lt_red) │ \
\n│ $(bold)$(white)%-66s$(normal)$(lt_red) │ \
\n│ $(bold)$(white)%-66s$(normal)$(lt_red) │ \
\n└────────────────────────────────────────────────────────────────────┘ \
\n\n$(clear)" "ERROR" "Refusing to flash dirty build to stable devices!" "" "BASE: $(BASE_VERSION)" " REV: $(REVISION)"
		exit 1
  ,)
,)
	$(call post_ota,broadcast_ota/$1/$(channel))

endef

define generate_env_targets =
$(call fimrware_template,$1)
$(call build_template,$1)
$(call ota_template,$1)

endef

active_ports = $(strip $(sort $(foreach d,$(devices),$(strip $(if $(wildcard /dev/$(call tty_by_id,$(word 2,$($(d))))),$(d),)))))

component_cmake = set(COMPONENT_SRCS\n$$(cd $1 && find $2 -type f \( -name '*.cpp' -o -name '*.c' \) -a ! -path '*/examples/*' -a ! -path '*/tests/*' -a ! -path '*/extras/*' | sort -u | sed -r 's/(.+)/  \"\1\"/g')\n)\n\nset(COMPONENT_ADD_INCLUDEDIRS\n$$(cd $1; for x in $$(find $2 -type f -name '*.h' -a ! -path '*/examples/*' -a ! -path '*/tests/*'); do echo $$(dirname $$x); done | sort -u | sed -r 's/(.*)/  \"\1\"/g')\n)\n\nset(COMPONENT_REQUIRES\n  arduino\n)\n\nregister_component()\n

include templates.mk

# Make targets start here

.PHONY: all build list devices list-ids flash bump-patch bump-minor bump-major \
		require_port require-env iterate iterate-ota flash-ota update-version-header \
		v version size size-components t tty usb status udev-rules update-idf erase-ota \
		fonts reconfigure-all ota ota-all clean fullclean clean-all fullclean-all \
		all-available docker menuconfig config

build:
	$(call require_args,env)
	$(MAKE) $(env)

all: $(build_envs)

all-available: $(envs)

$(foreach e,$(envs),$(eval $(call generate_env_targets,$(e))))

ota-all: $(addprefix ota-,$(build_envs))

list devices:
	@printf "$(bold)$(cyan)%-15s %-15s %-15s$(clear)" "Device" "Env" "Serial"
	@printf "$(foreach d,$(devices),\n$(bold)$(green)%-15s $(bold)$(yellow)%-15s$(clear) $(bold)%-15s$(clear))\n" $(foreach d,$(devices),"$(d)" "$(word 1,$($(d)))" "$(word 2,$($(d)))") | sort

flash:
	$(call require_args,env port)
	$(MAKE) $(env)
	$(call idf_py,$(env),flash -p $(TTY) -b $(FLASH_BAUD))

erase-ota:
	$(call idf_py,$(env),erase_otadata -p $(TTY) -b $(FLASH_BAUD))

ota: $(env)
	$(call require_args,env host)
	$(call post_ota,initiate_ota/$(host)/$(env))

add-commit-push:
	@git add -A \
		&& git status \
		&& sleep 0.5 \
		&& git commit \
		&& git push --set-upstream origin "$$(git rev-parse --abbrev-ref HEAD)"

	@if [ "$$(git rev-parse --abbrev-ref HEAD)" == "master" ] && [ "$(bump)" != "none" ]; then \
		$(call tag_version, v$(call bump_version, $(bump))) && \
		git push --tags; \
	else \
		echo "not bumping version"; \
	fi

tail:
	$(call require_args,port)
	$(call py3_tool,monitor.py -p $(TTY) -b $(BAUD_RATE) $(if $(reset),--reset,) --eol LF --elf $(call output_dir,$(env))/$(env).elf)

monitor:
	$(call require_args,host)
	mkdir -p logs/$(host)
	$(MAKE) tail 2>&1 | ts "%b %d %H:%M:%.S" | tee -a logs/$(host)/$(host).$$(date +%s).log

active_ports:
	$(foreach d,$(active_ports),$(MAKE) monitor id=$(subst esp32-,,$(d)) & ) wait

iterate-ota: ota
	$(MAKE) tail

iterate: flash
	$(MAKE) tail

update-version-header: | version
	@mkdir -p $$(dirname $(VERSION_HEADER_FILE))
	@printf '#pragma once\n\n// DO NOT MODIFY -- Generated by Makefile\n\n' > $(VERSION_HEADER_FILE)
	echo '#define SOFTWARE_VERSION "$(BASE_VERSION)"' >> $(VERSION_HEADER_FILE)
	echo '#define SOFTWARE_REVISION "$(REVISION)"' >> $(VERSION_HEADER_FILE)
	$(foreach e,$(envs),echo '$(BASE_VERSION)' > "projects/$(e)/version.txt";)

submodule-add-lib:
	$(call require_args,url)
	git submodule add $(if $(force),--force,) --name $$(basename $(url)) $(url) lib/$$(basename $(url))
	git submodule update --init --recursive

submodule-add-tool:
	$(call require_args,url)
	git submodule add $(if $(force),--force,) --name $$(basename $(url)) $(url) tools/$$(basename $(url))
	git submodule update --init --recursive

submodule-add-component:
	$(call require_args,url name)
	git submodule add $(if $(force),--force,) --name $(name) $(url) components/$(name)
	git submodule update --init --recursive

submodule-add-arduino:
	$(call require_args,url name)
	git submodule add $(if $(force),--force,) --name $(name) $(url) components/$(name)/$$(basename $(url))
	printf "$(call component_cmake,components/$(name),$$(basename $(url)))" > components/$(name)/CMakeLists.txt
	git submodule update --init --recursive


$(addprefix bump-,patch minor major):
	$(call tag_version, v$(call bump_version, $(filter-out bump-,$@)))


define create_example_template =
	$(call require_args,name folder)

	mkdir -p "bird_iot/$1/$(folder)"

	$(if $(force),,
		if [ -f "bird_iot/$1/$(folder)/$(name).cpp" ]; then \
			$(call print_error, '$(name)' already exists!); \
			exit 1; \
		fi
	)

	$(foreach ext,h cpp,\
		sed -r "s/$2/$(name)/g" \
			examples/$1/$2.$(ext) \
			| sed -r "s/$(call NameWithSpaces,$2)/$(call NameWithSpaces,$(name))/g" \
			| sed -r "s/$(call SNAKE_CASE,$2)/$(call SNAKE_CASE,$(name))/g" \
			| sed -r "s/$(call FilterOutPlugin,$2)/$(call FilterOutPlugin,$(name))/g" \
			| sed -r "s/$(call FirstWord,$(call NameWithSpaces,$2))/$(call FirstWord,$(call NameWithSpaces,$(name)))/g" \
			> bird_iot/$1/$(folder)/$(name).$(ext);\
	)

	$(if $3,
		echo '#include "$(name).h"' >> $(PLUGINS_INC_FILE)
		sed -i -r "s/(\s+)(menu \"Plugins\")/$(call MULTILINE,$3)/" bird_iot/Kconfig.projbuild
	,)
	$(if $4,
		sed -i -r "s/(\s+)(bool result = App.setupPlugins\(\);)/$(call MULTILINE,$4)/" bird_iot/modes/Runtime.cpp
	,)

	$(MAKE) reconfigure-all

	git add .

endef

create-class:
	$(call create_example_template,.,ExampleClass)

create-plugin:
	$(call create_example_template,plugins,ExampleBasicPlugin,PLUGIN_CONFIG,PLUGIN_REGISTER)

create-task-plugin:
	$(call create_example_template,plugins,ExampleTaskPlugin,PLUGIN_CONFIG,PLUGIN_REGISTER)

create-sensor:
	$(call create_example_template,plugins/sensors,ExampleSensorPlugin,SENSOR_MENUCONFIG,PROFILE_REGISTER)

create-temperature-sensor:
	$(call create_example_template,plugins/sensors/temperature,ExampleTempSensor,PLUGIN_CONFIG,PLUGIN_REGISTER)

clone-project:
	$(call require_args,from to)
	mkdir -p projects/$(to)
	cp projects/$(from)/partitions.csv projects/$(from)/sdkconfig projects/$(from)/CMakeLists.txt projects/$(to)/

# create the venv and install dependencies
first-run:
	$(virtualenv) venv
	$(MAKE) upgrade-all

# install/upgrade dependencies
upgrade-all:
	$(activate_venv) \
		&& pip3 install -U pip \
		&& pip3 install -r $(py_tools)/requirements.txt \
		&& pip3 install -r $${IDF_PATH}/requirements.txt

update-idf:
	$(activate_venv) \
 		&& cd $${IDF_PATH} \
		&& git pull --recurse-submodules \
		&& git status

v version:
	@echo "  BASE: $(BASE_VERSION)"
	@echo "   REV: $(REVISION)"

z zconf discover:
	$(call py3_tool,zconf.py --current-version $(BASE_VERSION))

ports tty usb t:
	$(call py3_tool,ports.py)

ws:
	$(call require_args,host)
	$(trap_ctrl_c) $(call py3_tool,ws.py $(host))

tail-ota:
	docker logs -f --tail 10 $$(docker ps -qf name=bird-ota_ota)

menuconfig config:
	$(call require_args,env)
	sdkconfig=$$(readlink -f $(call sdkconfig_file,$(env))); \
	before="$$(sha256sum $${sdkconfig})"; \
	($(call idf_py,$(env),menuconfig)); \
	after="$$(sha256sum $${sdkconfig})"; \
	if [ "$${before}" != "$${after}" ]; then \
		echo "$${before}"; \
		echo "$${after}"; \
		$(MAKE) reconfigure; \
	fi

reconfigure-all:
	$(foreach e,$(envs),$(MAKE) reconfigure env=$(e) & ) wait
	@printf "$(blue)Done$(clear)\n";

reconfigure clean fullclean:
	$(call require_args,env)
	$(call idf_py,$(env),$@)

size:
	$(call require_args,env)
	$(call py3_tool,sizer.py $(env))

size-components:
	$(call require_args,env)
	$(call idf_size_py, --archives $(call output_dir,$(env))/$(env).map)


define submake_env_template = 
$1-$2:
	$(MAKE) $1 env=$2

endef

$(foreach e,$(envs),$(foreach t,reconfigure menuconfig size size-components clean fullclean,$(eval $(call submake_env_template,$(t),$(e)))))

udev-rules:
	sudo cp -f 10-usb-serial.rules /etc/udev/rules.d/
	sudo udevadm control --reload-rules
	sudo udevadm trigger

status:
	git status

fonts:
	$(call py3_tool,fonts.py)

IDF_VER ?= v4.0.2
docker:
	docker build -f tools/docker/Dockerfile \
 		-t ajcasagrande/bird-iot:esp-idf-$(IDF_VER) \
 		--build-arg IDF_VER=$(IDF_VER) \
 		tools/
