from glob import glob
import os
import shutil

if __name__ == '__main__':
	# TODO: Check for multiple installation paths
	target = os.path.abspath(os.getenv('LOCALAPPDATA') + '\\Adobe\\Flash CS5.5\\en_US\\Configuration\\')
	target_commands = target + '\\Commands'

	print('Installing scripts at "' + target + '".')

	if not os.path.exists(target_commands):
		os.makedirs(target_commands)

	for f in glob('scripts\\commands\\*.jsfl'):
		print('Copying "' + os.path.basename(f) + '"...')
		from_path = os.path.abspath(f)
		to_path = os.path.abspath(target_commands + '\\' + os.path.basename(f))
		shutil.copy(from_path, to_path)