class Bitmap:
	def __init__(self, element):
		self.name = element.attrib.get('name', '')
		self.linkageIdentifier = element.attrib.get('linkageIdentifier', '')
		self.sourceExternalFilepath = element.attrib.get('sourceExternalFilepath', '')
		self.sourceLastImported = element.attrib.get('sourceLastImported', '')
		self.href = element.attrib.get('href', '')