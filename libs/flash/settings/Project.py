from libs.flash.settings.dom.Document import Document
from libs.flash.settings.Publish import Publish

class Project:
	def __init__(self, path):
		self.publish = Publish(path + '\\PublishSettings.xml')
		self.document = Document(path + '\\DOMDocument.xml')