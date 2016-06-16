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

function getSolutionTreeDataProvider()
{
	return IrisBuild.getSolutionTreeDataProvider();
}