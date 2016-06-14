from glob import glob
import fnmatch
import os
import shutil

def installFile(fromPath, toPath):
	print('Copying "' + fromPath + '"...')

	if not os.path.exists(os.path.dirname(toPath)):
		os.makedirs(os.path.dirname(toPath))

	shutil.copy(os.path.abspath(fromPath), toPath)

if __name__ == '__main__':
	languages = [ 'en_US' ]
	versions = [ 'Flash CS5.5', 'Flash CC 2015', 'Animate CC 2015' ]
	userpath = os.getenv('LOCALAPPDATA') + '\\Adobe\\'

	for v in versions:
		for l in languages:
			install = os.path.join(userpath, v, l)
			if not os.path.exists(install):
				continue

			print('Installing at "' + install + '".')

			target_iris = os.path.join(install, 'Configuration', 'IrisBuild')
			if not os.path.exists(target_iris):
				os.makedirs(target_iris)

			# Shared library

			target_libs = os.path.join(install, 'Configuration', 'External Libraries')
			if not os.path.exists(target_libs):
				os.makedirs(target_libs)

			if os.path.exists('output\\windows\\x64\\Release\\IrisBuild.dll'):
				installFile('output\\windows\\x64\\Release\\IrisBuild.dll', target_libs)
			elif os.path.exists('output\\windows\\x64\\Debug\\IrisBuild.dll'):
				installFile('output\\windows\\x64\\Debug\\IrisBuild.dll', target_libs)

			# Scripts

			target_commands = os.path.join(install, 'Configuration', 'Commands')
			if not os.path.exists(target_commands):
				os.makedirs(target_commands)

			for f in glob('scripts\\commands\\*.jsfl'):
				installFile(f, os.path.abspath(target_commands + '\\' + os.path.basename(f)))

			# GUI

			target_gui = os.path.join(install, 'Configuration', 'WindowSWF')
			if not os.path.exists(target_gui):
				os.makedirs(target_gui)

			installFile('build\\IrisBuildGUI.swf', target_gui)

			for f in glob('scripts\\gui\\jsfl\\*.jsfl'):
				installFile(f, os.path.abspath(target_iris + '\\jsfl\\' + os.path.basename(f)))