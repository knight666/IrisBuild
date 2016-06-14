import adobe.utils.MMExecute;
import flash.events.Event;
import flash.net.SharedObject;

private var _targetSolutionURI:String = "";

private function onCreationComplete(e:Event):void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (persistentData && persistentData.data.hasOwnProperty("IrisBuild_CurrentSolution"))
	{
		_targetSolutionURI = persistentData.data.IrisBuild_CurrentSolution;
	}
	
	MMExecute("IrisBuild.initialize(fl.configDirectory);");
}

private function btnLoadClicked(e:Event):void
{
	MMExecute("var result = IrisBuild.loadProject(flash.getDocumentDOM().path); fl.trace(\"\\\"\" + flash.getDocumentDOM().path + \"\\\" is \" + (result == \"true\" ? \"up-to-date\" : \"out-of-date\") + \".\");");
}