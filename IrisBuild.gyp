{
	'includes': [
		'build/common.gypi',
	],
	'targets': [
		{
			'target_name': 'IrisBuild',
			'type': 'shared_library',
			'sources': [
				'source/mm_jsapi.h',
				'source/main.c',
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