import os.path
import datetime

class IDependency:
	def __init__(self):
		self.cache_set = False
		self.cache_result = False

	def getTaskFilename(self):
		return '.'

	def getTaskCommand(self, path):
		return ''

	def getTaskDependencies(self):
		return []

	def reset(self):
		self.cache_set = False
		self.cache_result = False

		for d in self.getTaskDependencies():
			d.reset()

	def check(self, projectPath, intermediatePath):
		if self.cache_set:
			return self.cache_result

		print('Checking "' + self.getTaskFilename() + '"...')

		result = True

		intermediate = os.path.abspath(intermediatePath + '/' + self.getTaskFilename() + '.tlog')
		previous_command = ''
		current_command = ''

		if os.path.exists(intermediate):
			with open(intermediate, 'rb') as f:
				previous_command = f.read()

		current_command = self.getTaskCommand(projectPath)
		for d in self.getTaskDependencies():
			result = result and d.check(projectPath, intermediatePath)

			current_command += '\n'
			current_command += os.path.abspath(intermediatePath + '/' + d.getTaskFilename() + '.tlog')

		with open(intermediate, 'w+') as f:			
			f.write(current_command)

		self.cache_result = previous_command == str.encode(current_command)
		self.cache_set = True

		return self.cache_result
