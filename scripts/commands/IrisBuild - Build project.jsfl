IrisBuild.initialize(fl.configDirectory);

var result = IrisBuild.loadProject(flash.getDocumentDOM().path);
fl.trace("\"" + flash.getDocumentDOM().path + "\" is " + (result == "true" ? "up-to-date" : "out-of-date") + ".");