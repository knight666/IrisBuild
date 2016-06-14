import adobe.utils.MMExecute;
import flash.events.Event;
import flash.net.SharedObject;

private var _targetSolutionURI:String = "";

protected function execute(... parameters):String
{
	var scriptPath:String = "fl.runScript(fl.configURI + 'IrisBuild/jsfl/interface.jsfl', '" + parameters.shift().toString() + "'";
	
	var args:Array = [];
	for (var i:int = 0; i < parameters.length; i++)
	{
		args.push("'" + (parameters[i] || "").split("'").join("\'") + "'");
	}
	
	if (args.length > 0)
	{
		scriptPath += ", " + args.join(",");
	}
	
	scriptPath += ");";
	
	return MMExecute(scriptPath);
}

private function onCreationComplete(e:Event):void
{
	var persistentData:SharedObject = SharedObject.getLocal("persistentData");
	if (persistentData && persistentData.data.hasOwnProperty("IrisBuild_CurrentSolution"))
	{
		_targetSolutionURI = persistentData.data.IrisBuild_CurrentSolution;
	}
	
	execute("initialize");
}

private function btnLoadClicked(e:Event):void
{
	execute("loadProject");
}