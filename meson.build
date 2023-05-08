project('CEGE', 'cpp', default_options: ['cpp_std=c++20'])

dependencies = [
	dependency('fmt'),
	dependency('sdl2'),
	dependency('sdl2_image'),
	dependency('sdl2_ttf'),
]

executable(
	'main',
	'src/main.cpp',
	# dependencies: dependencies,
	win_subsystem: 'windows'
)