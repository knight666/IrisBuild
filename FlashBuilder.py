import libs.flash.Settings as fs 

if __name__ == '__main__':
	publish = fs.Publish()
	publish.parse('projects/TestEmpty/PublishSettings.xml')
	print('enabled', publish.enabled, 'publishPath', publish.publishPath, 'versionActionScript', publish.versionActionScript, 'packagePaths', publish.packagePaths, 'constants', publish.constants, 'documentClass', publish.documentClass)