import libs.flash.Settings as fs 

if __name__ == '__main__':
	project = fs.Project('projects/TestEmpty')
	print('enabled', project.publish.enabled, 'publishPath', project.publish.publishPath, 'versionActionScript', project.publish.versionActionScript, 'packagePaths', project.publish.packagePaths, 'constants', project.publish.constants, 'documentClass', project.publish.documentClass)