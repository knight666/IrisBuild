{
	'includes': [
		'build/common.gypi',
	],
	'targets': [
		{
			'target_name': 'utf8rewind',
			'type': 'static_library',
			'variables': {
				'project_dir': 'dependencies/utf8rewind-1.5.0',
			},
			'include_dirs': [
				'<(project_dir)/include/utf8rewind',
			],
			'sources': [
				'<(project_dir)/include/utf8rewind/utf8rewind.h',
				'<(project_dir)/source/internal/base.h',
				'<(project_dir)/source/internal/casemapping.c',
				'<(project_dir)/source/internal/casemapping.h',
				'<(project_dir)/source/internal/codepoint.c',
				'<(project_dir)/source/internal/codepoint.h',
				'<(project_dir)/source/internal/composition.c',
				'<(project_dir)/source/internal/composition.h',
				'<(project_dir)/source/internal/database.c',
				'<(project_dir)/source/internal/database.h',
				'<(project_dir)/source/internal/decomposition.c',
				'<(project_dir)/source/internal/decomposition.h',
				'<(project_dir)/source/internal/seeking.c',
				'<(project_dir)/source/internal/seeking.h',
				'<(project_dir)/source/internal/streaming.c',
				'<(project_dir)/source/internal/streaming.h',
				'<(project_dir)/source/unicodedatabase.c',
				'<(project_dir)/source/unicodedatabase.h',
				'<(project_dir)/source/utf8rewind.c',
			],
			'direct_dependent_settings': {
				'include_dirs': [
					'<(project_dir)/include/utf8rewind',
				],
			},
			'conditions': [
				['OS=="win"', {
					'msvs_settings': {
						'VCCLCompilerTool': {
							'CompileAs': 1, # Compile as C
						},
					},
				}],
				['OS!="win"', {
					'product_dir': 'output/<(platform_name)/<(architecture_name)/<(CONFIGURATION_NAME)',
				}],
			],
		},
		{
			'target_name': 'tinyxml',
			'type': 'static_library',
			'variables': {
				'project_dir': 'dependencies/tinyxml_2_6_2',
			},
			'include_dirs': [
				'<(project_dir)/include/utf8rewind',
			],
			'sources': [
				'<(project_dir)/tinystr.cpp',
				'<(project_dir)/tinystr.h',
				'<(project_dir)/tinyxml.cpp',
				'<(project_dir)/tinyxml.h',
				'<(project_dir)/tinyxmlerror.cpp',
				'<(project_dir)/tinyxmlparser.cpp',
			],
			'direct_dependent_settings': {
				'include_dirs': [
					'<(project_dir)',
				],
			},
			'conditions': [
				['OS!="win"', {
					'product_dir': 'output/<(platform_name)/<(architecture_name)/<(CONFIGURATION_NAME)',
				}],
			],
		},
	],
}