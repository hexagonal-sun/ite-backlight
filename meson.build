project(
  'ite-backlight', 'cpp',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ],
)

libusb_dep = dependency('libusb-1.0')
boost_dep = dependency('boost')
ite_backlight_dep = [libusb_dep, boost_dep]

ite_backlight_src = ['colour.cpp', 'speed.cpp', 'ite-device.cpp']

executable(
  'ite-mono',
  ['mono.cpp', ite_backlight_src],
  install : true,
  dependencies : ite_backlight_dep
)

executable(
  'ite-static',
  ['static.cpp', ite_backlight_src],
  install : true,
  dependencies : ite_backlight_dep
)

executable(
  'ite-breathe',
  ['breathe.cpp', ite_backlight_src],
  install : true,
  dependencies : ite_backlight_dep
)

executable(
  'ite-wave',
  ['wave.cpp', ite_backlight_src],
  install : true,
  dependencies : ite_backlight_dep
)

executable(
  'ite-flash',
  ['flash.cpp', ite_backlight_src],
  install : true,
  dependencies : ite_backlight_dep
)
