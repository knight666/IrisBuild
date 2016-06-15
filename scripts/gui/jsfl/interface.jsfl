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

function loadSolution(path)
{
	return IrisBuild.loadSolution(path);
}

function verifySolution()
{
	return IrisBuild.verifySolution();
}

function getSolutionTreeDataProvider()
{
	return IrisBuild.getSolutionTreeDataProvider();
}