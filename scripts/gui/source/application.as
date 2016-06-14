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
}

private function btnLoadClicked(e:Event):void
{
	MMExecute("fl.trace(\"Loading!\");");
}