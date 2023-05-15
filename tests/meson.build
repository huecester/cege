test_sources = [
	'main.test.cpp',
	'context.test.cpp',
	'component.test.cpp',
	'system.test.cpp',
]

test_dependencies = [
	dependency('doctest'),
]

test_exe = executable(
	'cege_test',
	test_sources,
	dependencies: libcege_dependencies + test_dependencies,
	link_with: libcege,
	include_directories: inccege,
)

test('unit tests', test_exe)