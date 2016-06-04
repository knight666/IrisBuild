import xml.etree.ElementTree as ET
from libs.flash.settings.dom.Bitmap import Bitmap

class Document:
	def __init__(self, filename):
		root = ET.parse(filename).getroot()

		self.bitmaps = []

		ns = { 'ns': 'http://ns.adobe.com/xfl/2008/' }

		media = root.find('ns:media', ns)
		if media:
			for b in media.findall('ns:DOMBitmapItem', ns):
				self.bitmaps.append(Bitmap(b))

		for b in self.bitmaps:
			print('name', b.name, 'linkageIdentifier', b.linkageIdentifier, 'sourceExternalFilepath', b.sourceExternalFilepath)