cege_dependencies = [
	dependency('glm'),
]

executable(
	'cege',
	'main.cpp',
	dependencies: cege_dependencies + libcege_dependencies,
	link_with: libcege,
	include_directories: inccege,
	win_subsystem: 'windows',
)