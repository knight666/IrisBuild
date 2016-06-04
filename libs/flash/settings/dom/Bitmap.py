import os.path
import time
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

	def getSourceFilename(self):
		return self.element.attrib.get('sourceExternalFilepath', '')

	def getTaskCommand(self, path):
		result = str.casefold(self.element.attrib.get('name', ''))
		result += ' ' + str.casefold(self.element.attrib.get('itemID', ''))
		result += ' ' + str.casefold(self.element.attrib.get('linkageExportForRS', ''))
		result += ' ' + str.casefold(self.element.attrib.get('linkageIdentifier', ''))
		result += ' ' + str.casefold(self.element.attrib.get('linkageURL', ''))
		result += ' ' + str.casefold(self.element.attrib.get('sourceExternalFilepath', ''))
		result += ' ' + str.casefold(self.element.attrib.get('sourceLastImported', ''))
		result += ' ' + str.casefold(self.element.attrib.get('allowSmoothing', ''))
		result += ' ' + str.casefold(self.element.attrib.get('useImportedJPEGData', ''))
		result += ' ' + str.casefold(self.element.attrib.get('compressionType', ''))
		result += ' ' + str.casefold(self.element.attrib.get('originalCompressionType', ''))
		result += ' ' + str.casefold(self.element.attrib.get('quality', ''))
		result += ' ' + str.casefold(self.element.attrib.get('href', ''))
		result += ' ' + str.casefold(self.element.attrib.get('bitmapDataHRef', ''))
		result += ' ' + str.casefold(self.element.attrib.get('frameRight', ''))
		result += ' ' + str.casefold(self.element.attrib.get('frameBottom', ''))

		return result
