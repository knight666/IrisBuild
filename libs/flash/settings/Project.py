import os
import os.path
from libs.flash.settings.dom.Document import Document
from libs.flash.settings.Publish import Publish

class Project:
	def __init__(self, path):
		self.path = path
		self.publish = Publish(path + '\\PublishSettings.xml')
		self.document = Document(path + '\\DOMDocument.xml')

		self.dependencies = [ self.publish, self.document ]

	def check(self):
		intermediate_path = self.path + '/intermediate'

		if not os.path.exists(intermediate_path):
			os.mkdir(intermediate_path)

		result = True

		for d in self.dependencies:
			if not d.check(self.path, intermediate_path):
				result = False

		return result