import xml.etree.ElementTree as ET

tree = ET.parse('projects/TestEmpty/PublishSettings.xml')
root = tree.getroot()
profile = root.find('flash_profile')
publish_settings = profile.find('PublishFormatProperties')
flash_fileName = publish_settings.find('flashFileName')

print('PublishFormatProperties')
print('enabled', publish_settings.attrib['enabled'])
print('flashFileName', flash_fileName.text)