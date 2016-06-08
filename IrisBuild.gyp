{
	'includes': [
		'build/common.gypi',
	],
	'targets': [
		{
			'target_name': 'IrisBuild',
			'type': 'shared_library',
			'dependencies': [
				'dependencies/utf8rewind-1.5.0/utf8rewind.gyp:utf8rewind',
			],
			'sources': [
				'source/helpers.cpp',
				'source/helpers.hpp',
				'source/interface.cpp',
				'source/interface.hpp',
				'source/mm_jsapi.h',
				'source/main.cpp',
			],
			'conditions': [
				['OS=="win"', {
					'msvs_settings': {
						'VCCLCompilerTool': {
							'TreatWChar_tAsBuiltInType': 'false',
						},
					},
				}],
			],
		},
	],
}