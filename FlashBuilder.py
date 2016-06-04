import xml.etree.ElementTree as ET

class PublishSettings:
	def __init__(self):
		pass

	def parse(self, filename):
		root = ET.parse(filename).getroot()

		profile = root.find('flash_profile')
		if not profile:
			raise SyntaxError('Missing "flash_profile" element in hierarchy.')

		publish_format = profile.find('PublishFormatProperties')
		if not publish_format:
			raise SyntaxError('Missing "PublishFormatProperties" element under "flash_profile" element.')

		self.enabled = publish_format.attrib['enabled'] == 'true'
		self.publishPath = self.readElement(publish_format, 'flashFileName')

		publish_flash = profile.find('PublishFlashProperties')
		if not publish_flash:
			raise SyntaxError('Missing "PublishFlashProperties" element under "flash_profile" element.')

		self.versionActionScript = self.readElement(publish_flash, 'ActionScriptVersion')
		if self.versionActionScript == '3':
			self.packagePaths = self.readElement(publish_flash, 'AS3PackagePaths')
			self.constants = self.readElement(publish_flash, 'AS3ConfigConst')
		else:
			self.packagePaths = self.readElement(publish_flash, 'PackagePaths')
			self.constants = []

		self.documentClass = self.readElement(publish_flash, 'DocumentClass')

	def readElement(self, parent, name):
		element = parent.find(name)
		if element == None:
			raise SyntaxError('Missing "' + str(name) + '" element under "' + str(parent.tag) + '" element.')

		return element.text

if __name__ == '__main__':
	publish = PublishSettings()
	publish.parse('projects/TestEmpty/PublishSettings.xml')
	print('enabled', publish.enabled, 'publishPath', publish.publishPath, 'versionActionScript', publish.versionActionScript, 'packagePaths', publish.packagePaths, 'constants', publish.constants, 'documentClass', publish.documentClass)