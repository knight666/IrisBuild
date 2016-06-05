from libs.flash.settings.Project import Project
import sys

if __name__ == '__main__':
	path = sys.argv[1]
	if not path:
		exit(-1)

	project = Project(path)
	result = project.check(True)
	print('path', path, 'result', result)

	with open('blah.txt', 'w+') as f:
		f.write('blah')