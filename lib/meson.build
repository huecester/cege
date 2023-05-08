libcege_sources = [
	'context.cpp',
	'sdl/texture.cpp',
	'sdl/util.cpp',
	'sdl/window.cpp',
]

libcege_dependencies = [
	dependency('sdl2'),
	dependency('sdl2_image'),
]

libcege = library(
	'cege',
	libcege_sources,
	dependencies: libcege_dependencies,
)

inccege = include_directories('.')