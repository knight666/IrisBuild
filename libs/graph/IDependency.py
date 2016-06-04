import os.path
import datetime

class IDependency:
	def __init__(self):
		self.cache_set = False
		self.cache_result = False

	def getTaskFilename(self):
		return '.'

	def getSourceFilename(self):
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

		# Build task command output

		command = [ self.getTaskCommand(projectPath) ]
		for d in self.getTaskDependencies():
			result = result and d.check(projectPath, intermediatePath, verbose)
			command.append(os.path.abspath(intermediatePath + '/' + d.getTaskFilename() + '.tlog'))

		command_binary = str.encode('\n'.join(command))

		if verbose:
			print('Checking "' + self.getTaskFilename() + '"...')

		# Check timestamps on source and intermediate file

		source = os.path.abspath(projectPath + self.getSourceFilename())
		if os.path.exists(source):
			source_time = os.path.getmtime(source)

		intermediate = os.path.abspath(intermediatePath + '/' + self.getTaskFilename() + '.tlog')
		if os.path.exists(intermediate):
			intermediate_time = os.path.getmtime(intermediate)
		else:
			intermediate_time = datetime.now()

		result = source_time <= intermediate_time

		# Check previously stored command output with current command output

		if result:
			if os.path.exists(intermediate):
				with open(intermediate, 'rb') as f:
					command_previous = f.read()
			else:
				command_previous = ''	

			result = command_previous == command_binary

		# Write intermediate file

		if not result:
			if not os.path.exists(os.path.dirname(intermediate)):
				os.makedirs(os.path.dirname(intermediate))

			with open(intermediate, 'wb+') as f:
				f.write(command_binary)

		# Store result

		if verbose and not result:
			print('Out of date.')

		self.cache_result = result
		self.cache_set = True

		return self.cache_result
