import os.path
import datetime

class IDependency:
	def getTaskFilename(self):
		return '.'

	def getTaskCommand(self, path):
		return ''

	def getDependencies(self):
		return []