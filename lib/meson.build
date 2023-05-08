libcege_sources = [
	'context.cpp',
	'util.cpp',
	'window.cpp',
]

libcege_dependencies = [
	dependency('sdl2'),
]

libcege = library(
	'cege',
	libcege_sources,
	dependencies: libcege_dependencies,
)

inccege = include_directories('.')