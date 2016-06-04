import xml.etree.ElementTree as ET
from libs.flash.settings.dom.Bitmap import Bitmap
from libs.graph.IDependency import IDependency

class Document(IDependency):
	def __init__(self, filename):
		super().__init__()

		self.root = ET.parse(filename).getroot()
		ns = { 'ns': 'http://ns.adobe.com/xfl/2008/' }

		self.bitmaps = []

		media = self.root.find('ns:media', ns)
		if media:
			for b in media.findall('ns:DOMBitmapItem', ns):
				self.bitmaps.append(Bitmap(b))

	def getTaskFilename(self):
		return './DOMDocument'

	def getTaskCommand(self, path):
		result = str.casefold(self.root.attrib.get('backgroundColor', ''))
		result += ' ' + str.casefold(self.root.attrib.get('width', ''))
		result += ' ' + str.casefold(self.root.attrib.get('height', ''))
		result += ' ' + str.casefold(self.root.attrib.get('frameRate', ''))
		result += ' ' + str.casefold(self.root.attrib.get('currentTimeline', ''))
		result += ' ' + str.casefold(self.root.attrib.get('xflVersion', ''))
		result += ' ' + str.casefold(self.root.attrib.get('creatorInfo', ''))
		result += ' ' + str.casefold(self.root.attrib.get('platform', ''))
		result += ' ' + str.casefold(self.root.attrib.get('versionInfo', ''))
		result += ' ' + str.casefold(self.root.attrib.get('majorVersion', ''))
		result += ' ' + str.casefold(self.root.attrib.get('minorVersion', ''))
		result += ' ' + str.casefold(self.root.attrib.get('buildNumber', ''))
		result += ' ' + str.casefold(self.root.attrib.get('viewAngle3D', ''))
		result += ' ' + str.casefold(self.root.attrib.get('sharedLibraryURL', ''))
		result += ' ' + str.casefold(self.root.attrib.get('nextSceneIdentifier', ''))
		result += ' ' + str.casefold(self.root.attrib.get('playOptionsPlayLoop', ''))
		result += ' ' + str.casefold(self.root.attrib.get('playOptionsPlayPages', ''))
		result += ' ' + str.casefold(self.root.attrib.get('playOptionsPlayFrameActions', ''))

		return result

	def getTaskDependencies(self):
		result = []
		result += self.bitmaps

		return result