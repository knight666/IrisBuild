import os

if __name__ == '__main__':
	target = os.path.abspath(os.getenv('LOCALAPPDATA') + '\\Adobe\\Flash CC\\language\\Configuration\\')
	print(target)