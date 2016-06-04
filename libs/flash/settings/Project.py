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

	def check(self, verbose=False):
		intermediate_path = self.path + '/intermediate'

		result = True

		for d in self.dependencies:
			if not d.check(self.path, intermediate_path, verbose):
				result = False

		return result