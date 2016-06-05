FLfile.runCommandLine('python FlashBuilder.py');
fl.trace(flash.documents[0].name);
fl.trace(FLfile.uriToPlatformPath(fl.scriptURI));
fl.trace(flash.getDocumentDOM().path);