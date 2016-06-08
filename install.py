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

			target = os.path.join(install, 'Configuration', 'Commands')

			print('Installing at "' + target + '".')

			if not os.path.exists(target):
				os.makedirs(target)

			if os.path.exists('output\\windows\\Win32\\Release\\IrisBuild.dll'):
				installFile('output\\windows\\Win32\\Release\\IrisBuild.dll', target)
			elif os.path.exists('output\\windows\\Win32\\Debug\\IrisBuild.dll'):
				installFile('output\\windows\\Win32\\Debug\\IrisBuild.dll', target)

			for f in glob('scripts\\commands\\*.jsfl'):
				installFile(f, os.path.abspath(target + '\\' + os.path.basename(f)))

			installFile('FlashBuilder.py', target)

			for root, dirnames, filenames in os.walk('libs'):
				for filename in fnmatch.filter(filenames, '*.py'):
					installFile(os.path.join(root, filename), os.path.join(target, 'libs', *dirnames) + '\\' + filename)