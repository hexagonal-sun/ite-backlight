project(
  'ite-backlight', 'cpp',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ],
)

libusb_dep = dependency('libusb-1.0')

executable(
  'ite-backlight',
  'main.cpp',
  install : true,
  dependencies : libusb_dep
)
