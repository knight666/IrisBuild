from libs.flash.settings.dom.Document import Document
from libs.flash.settings.Publish import Publish

class Project:
	def __init__(self, path):
		self.path = path
		self.publish = Publish(path + '\\PublishSettings.xml')
		self.document = Document(path + '\\DOMDocument.xml')

	def check(self):
		print(self.publish.getTaskFilename())
		print(self.publish.getTaskCommand(self.path))
		print(self.document.getTaskFilename())
		print(self.document.getTaskCommand(self.path))