from glob import glob
import os
import shutil

def installFile(fromPath, toPath):
	print('Copying "' + fromPath + '"...')

	if not os.path.exists(os.path.dirname(toPath)):
		os.makedirs(os.path.dirname(toPath))

	shutil.copy(os.path.abspath(fromPath), toPath)

if __name__ == '__main__':
	# TODO: Check for multiple installation paths
	target = os.path.abspath(os.getenv('LOCALAPPDATA') + '\\Adobe\\Flash CS5.5\\en_US\\Configuration\\Commands')

	print('Installing at "' + target + '".')

	if not os.path.exists(target):
		os.makedirs(target)

	for f in glob('scripts\\commands\\*.jsfl'):
		installFile(f, os.path.abspath(target + '\\' + os.path.basename(f)))

	installFile('FlashBuilder.py', target)

	for f in glob('libs\\**\\*.py', recursive=True):
		installFile(f, target + '\\' + f)