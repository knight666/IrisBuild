from libs.flash.settings.Project import Project

if __name__ == '__main__':
	project = Project('projects/TestEmpty')
	print('enabled', project.publish.enabled, 'publishPath', project.publish.publishPath, 'versionActionScript', project.publish.versionActionScript, 'packagePaths', project.publish.packagePaths, 'constants', project.publish.constants, 'documentClass', project.publish.documentClass)