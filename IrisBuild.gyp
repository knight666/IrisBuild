{
	'includes': [
		'build/common.gypi',
	],
	'targets': [
		{
			'target_name': 'IrisBuild',
			'type': 'shared_library',
			'dependencies': [
				'dependencies.gyp:utf8rewind',
				'dependencies.gyp:tinyxml',
			],
			'sources': [
				'source/build/dom/bitmapitem.cpp',
				'source/build/dom/bitmapitem.hpp',
				'source/build/dom/document.cpp',
				'source/build/dom/document.hpp',
				'source/build/dom/symbol.cpp',
				'source/build/dom/symbol.hpp',
				'source/build/buildvisitor.cpp',
				'source/build/buildvisitor.hpp',
				'source/build/project.cpp',
				'source/build/project.hpp',
				'source/build/publish.cpp',
				'source/build/publish.hpp',
				'source/build/solution.cpp',
				'source/build/solution.hpp',
				'source/build/task.cpp',
				'source/build/task.hpp',
				'source/build/treevisitor.cpp',
				'source/build/treevisitor.hpp',
				'source/build/visitor.hpp',
				'source/logging/logger.cpp',
				'source/logging/logger.hpp',
				'source/application.cpp',
				'source/application.hpp',
				'source/helpers.cpp',
				'source/helpers.hpp',
				'source/interface.cpp',
				'source/interface.hpp',
				'source/mm_jsapi.h',
				'source/main.cpp',
				'source/main.hpp',
				'source/scripting.cpp',
				'source/scripting.hpp',
			],
			'conditions': [
				['OS=="win"', {
					'libraries': [
						'Shell32.lib',
						'Shlwapi.lib'
					],
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