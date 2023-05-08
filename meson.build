project('CEGE', 'cpp', default_options: ['cpp_std=c++20'])

# dependencies = [
# 	dependency('fmt'),
# 	dependency('sdl2'),
# 	dependency('sdl2_image'),
# 	dependency('sdl2_ttf'),
# ]

test_dependencies = [
	dependency('doctest'),
]

test_exe = executable(
	'cege_test',
	'tests/main.cpp',
	dependencies: test_dependencies,
)

test('unit tests', test_exe)

executable(
	'cege',
	'src/main.cpp',
	# dependencies: dependencies,
	win_subsystem: 'windows',
)