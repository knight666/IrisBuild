fl.trace(flash.getDocumentDOM().path);
var command = "\"" + fl.configDirectory + "Commands\\FlashBuilder.py\" \"" + flash.getDocumentDOM().path + "\"";
fl.trace(command);
FLfile.runCommandLine(command);