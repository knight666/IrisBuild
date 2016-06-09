var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
if (!result)
{
	fl.trace("Failed to load uncompressed file \"" + flash.getDocumentDOM().path + "\", check the log for errors.");
}
else
{
	fl.trace("input " + flash.getDocumentDOM().path + " output " + result);
}