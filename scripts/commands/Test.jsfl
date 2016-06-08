fl.trace(flash.getDocumentDOM().path);
var command = "\"" + fl.configDirectory + "Commands\\FlashBuilder.py\" \"" + flash.getDocumentDOM().path + "\"";
fl.trace(command);
FLfile.runCommandLine(command);

var a = 5;
var b = 10;
var sum = IrisBuild.computeSum(a, b);
fl.trace("The sum of " + a + " and " + b + " is " + sum );