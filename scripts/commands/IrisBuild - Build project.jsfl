var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
if (!result)
{
	fl.trace("Project must be loaded as an uncompressed .xfl file, not a .fla file.");
}
else
{
	fl.trace("input " + flash.getDocumentDOM().path + " output " + result);
}