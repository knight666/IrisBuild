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
	var filePath = fl.browseForFileURL("open", "Select a solution file.", "IrisBuild Solution (*.xml)", "xml");
	//return FLfile.uriToPlatformPath(filePath);
	return filePath;
}

function loadSolution(path)
{
	return IrisBuild.loadSolution(path);
}