function initialize()
{
	IrisBuild.initialize(fl.configDirectory);
}

function loadProject()
{
	var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
	fl.trace("\"" + flash.getDocumentDOM().path + "\" is " + (result == "true" ? "up-to-date" : "out-of-date") + ".");
}