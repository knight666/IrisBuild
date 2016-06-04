import os.path
from libs.graph.IDependency import IDependency

class Bitmap(IDependency):
	def __init__(self, element):
		super().__init__()
		
		self.element = element
		self.name = element.attrib.get('name', '')
		self.linkageIdentifier = element.attrib.get('linkageIdentifier', '')
		self.sourceExternalFilepath = element.attrib.get('sourceExternalFilepath', '')
		self.sourceLastImported = element.attrib.get('sourceLastImported', '')
		self.href = element.attrib.get('href', '')

	def getTaskFilename(self):
		return './media/bitmaps/' + str.casefold(self.name)

	def getTaskCommand(self, path):
		result = str.casefold(self.root.attrib.get('name', ''))
		result += ' ' + str.casefold(self.root.attrib.get('itemID', ''))
		result += ' ' + str.casefold(self.root.attrib.get('linkageExportForRS', ''))
		result += ' ' + str.casefold(self.root.attrib.get('linkageIdentifier', ''))
		result += ' ' + str.casefold(self.root.attrib.get('linkageURL', ''))
		result += ' ' + str.casefold(self.root.attrib.get('sourceExternalFilepath', ''))
		result += ' ' + str.casefold(self.root.attrib.get('sourceLastImported', ''))
		result += ' ' + str.casefold(self.root.attrib.get('allowSmoothing', ''))
		result += ' ' + str.casefold(self.root.attrib.get('useImportedJPEGData', ''))
		result += ' ' + str.casefold(self.root.attrib.get('compressionType', ''))
		result += ' ' + str.casefold(self.root.attrib.get('originalCompressionType', ''))
		result += ' ' + str.casefold(self.root.attrib.get('quality', ''))
		result += ' ' + str.casefold(self.root.attrib.get('href', ''))
		result += ' ' + str.casefold(self.root.attrib.get('bitmapDataHRef', ''))
		result += ' ' + str.casefold(self.root.attrib.get('frameRight', ''))
		result += ' ' + str.casefold(self.root.attrib.get('frameBottom', ''))

		filepath = os.path.abspath(path + self.sourceExternalFilepath)
		print(filepath)

		return result
