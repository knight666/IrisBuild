from libs.flash.settings.Project import Project

if __name__ == '__main__':
	path = 'projects/TestEmpty'

	project = Project(path)
	result = project.check(True)
	print('path', path, 'result', result)