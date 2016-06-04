def readElement(parent, name):
	element = parent.find(name)
	if element == None:
		raise SyntaxError('Missing "' + str(name) + '" element under "' + str(parent.tag) + '" element.')

	if element.text == None:
		return ''
	
	return element.text

def readPathList(value):
	return value.split(';')