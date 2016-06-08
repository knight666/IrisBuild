fl.trace(flash.getDocumentDOM().path);
var command = "\"" + fl.configDirectory + "Commands\\FlashBuilder.py\" \"" + flash.getDocumentDOM().path + "\"";
fl.trace(command);
FLfile.runCommandLine(command);

fl.trace(JSFLBitWriter);
fl.trace(JSFLBitWriter.openFile);
for (var prop in JSFLBitWriter)
{
	fl.trace(prop + " = " + JSFLBitWriter[prop]);
}

fl.trace(IrisBuild);
fl.trace(IrisBuild.computeSum);
fl.trace(IrisBuild.openFile);
for (var prop in IrisBuild)
{
	fl.trace(prop + " = " + IrisBuild[prop]);
}

/*var a = 5;
var b = 10;
var sum = IrisBuild.computeSum(a, b);
fl.trace("The sum of " + a + " and " + b + " is " + sum );*/