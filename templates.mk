
MULTILINE = $(subst $(newline),\n,$($1))

define PLUGIN_REGISTER
\#if CONFIG_ENABLE_$(call SNAKE_CASE,$(name))
\1App.registerPlugin(\&$(call FilterOutPlugin,$(name)));
\#endif

\1\2
endef

define PROFILE_REGISTER
\#if CONFIG_ENABLE_$(call SNAKE_CASE,$(name))
\1registerIf(p->$(name)Enabled(), new $(name)());
\#endif

\1\2
endef

define PLUGIN_CONFIG
\1\2

\1  config ENABLE_$(call SNAKE_CASE,$(name))
\1    bool \"$(call NameWithSpaces,$(name))\"
\1    default $(default)

endef

define SENSOR_MENUCONFIG
\1\2

\1  menuconfig ENABLE_$(call SNAKE_CASE,$(name))
\1    bool \"$(call NameWithSpaces,$(name))\"
\1    default $(default)

\1    config $(call SNAKE_CASE,$(name))_POLL_INTERVAL
\1      int \"$(call NameWithSpaces,$(name)PollInterval)\"
\1      depends on ENABLE_$(call SNAKE_CASE,$(name))
\1      default 1000

\1    config $(call SNAKE_CASE,$(name))_PUBLISH_INTERVAL
\1      int \"$(call NameWithSpaces,$(name)PublishInterval)\"
\1      depends on ENABLE_$(call SNAKE_CASE,$(name))
\1      default 30000

endef
