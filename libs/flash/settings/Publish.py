import xml.etree.ElementTree as ET
import libs.flash.XMLUtils as fxml

class Publish:
	def __init__(self, filename):
		root = ET.parse(filename).getroot()

		profile = root.find('flash_profile')
		if not profile:
			raise SyntaxError('Missing "flash_profile" element in hierarchy.')

		publish_format = profile.find('PublishFormatProperties')
		if not publish_format:
			raise SyntaxError('Missing "PublishFormatProperties" element under "flash_profile" element.')

		self.enabled = publish_format.attrib['enabled'] == 'true'
		self.publishPath = fxml.readElement(publish_format, 'flashFileName')

		publish_flash = profile.find('PublishFlashProperties')
		if not publish_flash:
			raise SyntaxError('Missing "PublishFlashProperties" element under "flash_profile" element.')

		self.versionActionScript = fxml.readElement(publish_flash, 'ActionScriptVersion')
		if self.versionActionScript == '3':
			self.packagePaths = fxml.readPathList(fxml.readElement(publish_flash, 'AS3PackagePaths'))
			self.constants = fxml.readPathList(fxml.readElement(publish_flash, 'AS3ConfigConst'))
		else:
			self.packagePaths = fxml.readPathList(fxml.readElement(publish_flash, 'PackagePaths'))
			self.constants = []

		self.documentClass = fxml.readElement(publish_flash, 'DocumentClass')