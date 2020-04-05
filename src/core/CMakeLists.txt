project(umscore VERSION 0.9)

add_library(umscore SHARED
  core.c
  builder.c
  device.c
  error.c
  generator.c
  list.c
  logger.c
  object.c
  property.c
  signals.c
  signals_alias.c
  signals_receiver.c
  signals_sender.c
  simulator.c
  value.c
)
