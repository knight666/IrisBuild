import xml.etree.ElementTree as ET

class Document:
	def __init__(self, filename):
		root = ET.parse(filename).getroot()
		print(root.tag, root.attrib)