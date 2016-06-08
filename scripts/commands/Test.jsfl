fl.trace(flash.getDocumentDOM().path);
var command = "\"" + fl.configDirectory + "Commands\\FlashBuilder.py\" \"" + flash.getDocumentDOM().path + "\"";
fl.trace(command);
FLfile.runCommandLine(command);

var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
fl.trace("input " + flash.getDocumentDOM().path + " output " + result);