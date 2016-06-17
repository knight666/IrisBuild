function initialize()
{
	IrisBuild.initialize(fl.configDirectory);
}

function loadProject()
{
	var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
	fl.trace("\"" + flash.getDocumentDOM().path + "\" is " + (result == "true" ? "up-to-date" : "out-of-date") + ".");
}

function openSolution()
{
	return fl.browseForFileURL("open", "Select a solution file.", "IrisBuild Solution (*.xml)", "xml");
}

function createSolution()
{
	path = fl.browseForFileURL("save", "Specify a filename for the solution file.", "IrisBuild Solution (*.xml)", "xml");
	return IrisBuild.createSolution(path) == "true" ? path : null;
}

function loadSolution(path)
{
	return IrisBuild.loadSolution(path) == "true";
}

function verifySolution()
{
	return IrisBuild.verifySolution() == "true";
}

function addProject()
{
	var path = fl.browseForFileURL("select", "Select a project file.", "Flash Uncompressed Document (*.xfl)", "xfl");
	if (!path)
	{
		return false;
	}
	
	return IrisBuild.addProject(path) == "true";
}

function removeProject(path)
{
	return IrisBuild.removeProject(path) == "true";
}

function getSolutionTreeDataProvider()
{
	return IrisBuild.getSolutionTreeDataProvider();
}

function getProjectsOutOfDate()
{
	return IrisBuild.getProjectsOutOfDate();
}

function getSettingInt(setting)
{
	return IrisBuild.getSettingInt(setting);
}

function getSettingString(setting)
{
	return IrisBuild.getSettingString(setting);
}

function setSettingInt(setting, value)
{
	IrisBuild.setSettingInt(setting, value);
}

function setSettingString(setting, value)
{
	IrisBuild.setSettingString(setting, value);
}