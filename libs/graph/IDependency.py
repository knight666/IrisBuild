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

	def check(self, projectPath, intermediatePath, verbose=False):
		if self.cache_set:
			return self.cache_result

		result = True

		intermediate = os.path.abspath(intermediatePath + '/' + self.getTaskFilename() + '.tlog')
		previous_command = ''
		current_command = ''

		if not os.path.exists(os.path.dirname(intermediate)):
			os.makedirs(os.path.dirname(intermediate))

		if os.path.exists(intermediate):
			with open(intermediate, 'rb') as f:
				previous_command = f.read()

		with open(intermediate, 'w+') as f:
			current_command = self.getTaskCommand(projectPath)
			f.write(current_command)

			for d in self.getTaskDependencies():
				result = result and d.check(projectPath, intermediatePath, verbose)

				command = os.path.abspath(intermediatePath + '/' + d.getTaskFilename() + '.tlog')
				f.write('\n' + command)

				current_command += '\r\n' + command

		if verbose:
			print('Checking "' + self.getTaskFilename() + '"...')

		self.cache_result = previous_command == str.encode(current_command)
		self.cache_set = True

		if verbose and not self.cache_result:
			print('Out of date.')

		return self.cache_result
